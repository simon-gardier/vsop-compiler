/**
 * @brief LLVM IR code generator implementation for VSOP compiler
 */

#include "codegen.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
// LLVM casting utilities
#include "llvm/Support/Casting.h"

namespace VSOP
{
    CodeGenerator::CodeGenerator()
        : context(std::make_unique<llvm::LLVMContext>()),
          module(std::make_unique<llvm::Module>("vsop_program", *context)),
          builder(std::make_unique<llvm::IRBuilder<>>(*context)),
          currentFunction(nullptr),
          currentBlock(nullptr)
    {
        initializeTypes();
    }

    CodeGenerator::~CodeGenerator() = default;

    void CodeGenerator::initializeTypes()
    {
        // Map VSOP types to LLVM types
        typeMap["int32"] = llvm::Type::getInt32Ty(*context);
        typeMap["bool"] = llvm::Type::getInt1Ty(*context);
        // i8*
        typeMap["string"] = llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0);
        typeMap["unit"] = llvm::Type::getVoidTy(*context);
    }

    std::string CodeGenerator::generateCode(SemanticAnalyzer *semanticAnalyzer)
    {
        if (!semanticAnalyzer)
        {
            return "";
        }

        try
        {
            // Generate class types first
            generateClassTypes(semanticAnalyzer);

            // Generate vtable types
            generateVTableTypes(semanticAnalyzer);

            // Generate global variables
            generateGlobalVariables(semanticAnalyzer);

            // Generate functions
            generateFunctions(semanticAnalyzer);

            // Generate main function
            generateMainFunction(semanticAnalyzer);

            // Convert module to string
            std::string moduleStr;
            llvm::raw_string_ostream rso(moduleStr);
            module->print(rso, nullptr);
            irString = rso.str();

            return irString;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error during code generation: " << e.what() << std::endl;
            return "";
        }
    }

    void CodeGenerator::generateClassTypes(SemanticAnalyzer *semanticAnalyzer)
    {
        const auto &classes = semanticAnalyzer->getClasses();

        // First, ensure opaque structs exist for all classes and their vtables
        ensureEmptyTypes(classes);

        // Build field layouts with inheritance and set bodies
        for (const auto &classPair : classes)
        {
            const std::string &className = classPair.first;
            buildClassFieldLayout(className, classes);
        }
    }

    void CodeGenerator::generateVTableTypes(SemanticAnalyzer *semanticAnalyzer)
    {
        const auto &classes = semanticAnalyzer->getClasses();
        // Build method layouts including inheritance/overrides
        for (const auto &classPair : classes)
        {
            const std::string &className = classPair.first;
            buildClassVTableLayout(className, classes);
        }

        // Set vtable type bodies according to order
        for (const auto &classPair : classes)
        {
            const std::string &className = classPair.first;
            auto vtableIt = vtableTypeMap.find(className);
            if (vtableIt == vtableTypeMap.end())
                continue;
            auto clsTy = classTypeMap[className];
            std::vector<llvm::Type *> fieldTys;
            for (const auto &mname : vtableOrderMap[className])
            {
                // Lookup signature in class hierarchy
                MethodSignature ms;
                std::string cur = className;
                while (!cur.empty())
                {
                    auto itc = classes.find(cur);
                    if (itc == classes.end())
                        break;
                    if (itc->second.methods.count(mname))
                    {
                        ms = itc->second.methods.at(mname);
                        break;
                    }
                    if (itc->second.parent == cur)
                        break;
                    cur = itc->second.parent;
                }
                std::vector<llvm::Type *> params;
                params.push_back(llvm::PointerType::get(clsTy, 0));
                for (const auto &pt : ms.parameterTypes)
                    params.push_back(getLLVMType(pt.toString()));
                auto fty = llvm::FunctionType::get(getLLVMType(ms.returnType.toString()), params, false);
                fieldTys.push_back(llvm::PointerType::get(fty, 0));
            }
            vtableIt->second->setBody(fieldTys);
        }
    }

    void CodeGenerator::generateGlobalVariables(SemanticAnalyzer *semanticAnalyzer)
    {
        // Generate vtable global variables
        const auto &classes = semanticAnalyzer->getClasses();

        for (const auto &classPair : classes)
        {
            const std::string &className = classPair.first;
            // const ClassInfo &classInfo = classPair.second; // unused

            // Create vtable global variable
            std::string vtableName = className + "_vtable";
            auto vtableIt = vtableTypeMap.find(className);
            if (vtableIt != vtableTypeMap.end())
            {
                auto *gv = new llvm::GlobalVariable(
                    *module,
                    vtableIt->second,
                    true, // constant after init
                    llvm::GlobalValue::InternalLinkage,
                    llvm::UndefValue::get(vtableIt->second), // temporary initializer
                    vtableName);
                vtableGlobals[className] = gv;
            }
        }
    }

    void CodeGenerator::generateFunctions(SemanticAnalyzer *semanticAnalyzer)
    {
        const auto &classes = semanticAnalyzer->getClasses();

        for (const auto &classPair : classes)
        {
            const std::string &className = classPair.first;
            const ClassInfo &classInfo = classPair.second;

            // Create 'new_Class' function
            llvm::FunctionType *newType = llvm::FunctionType::get(
                llvm::PointerType::get(classTypeMap[className], 0),
                false);
            std::string newName = "new_" + className;
            llvm::Function *newFunc = llvm::Function::Create(
                newType, llvm::Function::ExternalLinkage, newName, module.get());
            {
                llvm::BasicBlock *entry = llvm::BasicBlock::Create(*context, "entry", newFunc);
                builder->SetInsertPoint(entry);

                // size via gep null trick
                auto nullPtr = llvm::ConstantPointerNull::get(llvm::PointerType::get(classTypeMap[className], 0));
                auto one32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1);
                auto sizePtr = builder->CreateGEP(classTypeMap[className], nullPtr, {one32});
                auto size64 = builder->CreatePtrToInt(sizePtr, llvm::Type::getInt64Ty(*context));
                // malloc and bitcast
                llvm::Function *mallocF = module->getFunction("malloc");
                if (!mallocF)
                {
                    auto retTy = llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0);
                    auto fty = llvm::FunctionType::get(retTy, {llvm::Type::getInt64Ty(*context)}, false);
                    mallocF = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, "malloc", module.get());
                }
                auto raw = builder->CreateCall(mallocF, {size64});
                auto obj = builder->CreateBitCast(raw, llvm::PointerType::get(classTypeMap[className], 0));

                // Call init
                std::string initName = "init_" + className;
                llvm::Function *initFunc = module->getFunction(initName);
                if (!initFunc)
                {
                    auto initTy = llvm::FunctionType::get(llvm::PointerType::get(classTypeMap[className], 0), {llvm::PointerType::get(classTypeMap[className], 0)}, false);
                    initFunc = llvm::Function::Create(initTy, llvm::Function::ExternalLinkage, initName, module.get());
                }
                auto initialized = builder->CreateCall(initFunc, {obj});
                builder->CreateRet(initialized);
            }

            // Define 'init_Class' function
            llvm::Function *initFunc = module->getFunction("init_" + className);
            if (!initFunc)
            {
                auto initTy = llvm::FunctionType::get(llvm::PointerType::get(classTypeMap[className], 0), {llvm::PointerType::get(classTypeMap[className], 0)}, false);
                initFunc = llvm::Function::Create(initTy, llvm::Function::ExternalLinkage, "init_" + className, module.get());
            }
            {
                llvm::BasicBlock *entry = llvm::BasicBlock::Create(*context, "entry", initFunc);
                builder->SetInsertPoint(entry);
                auto selfArg = initFunc->arg_begin();
                selfArg->setName("self");
                llvm::Value *self = &*selfArg;

                // Set vtable pointer field [0,0]
                auto zero32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
                auto vtablePtr = builder->CreateGEP(classTypeMap[className], self, {zero32, zero32});
                auto vtIt = vtableGlobals.find(className);
                if (vtIt != vtableGlobals.end())
                {
                    builder->CreateStore(vtIt->second, vtablePtr);
                }

                // Initialize fields with default values
                unsigned fieldIndex = 1; // 0 is vtable
                for (const auto &fieldPair : classInfo.fields)
                {
                    const Type &ft = fieldPair.second;
                    llvm::Type *fty = getLLVMType(ft.toString());
                    auto gep = builder->CreateGEP(classTypeMap[className], self, {zero32, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), fieldIndex)});
                    builder->CreateStore(getDefaultValue(fty), gep);
                    fieldIndex++;
                }

                builder->CreateRet(self);
            }

            // Prepare to collect method function pointers for vtable init (by slot order)
            std::vector<llvm::Constant *> vtableFuncs(vtableOrderMap[className].size(), nullptr);
            // Generate methods for this class
            for (const auto &methodPair : classInfo.methods)
            {
                const MethodSignature &methodSig = methodPair.second;

                // Create function name: ClassName_methodName
                std::string funcName = className + "_" + methodSig.name;

                // Create function type
                std::vector<llvm::Type *> paramTypes;
                paramTypes.push_back(llvm::PointerType::get(classTypeMap[className], 0)); // self parameter

                for (const Type &paramType : methodSig.parameterTypes)
                {
                    paramTypes.push_back(getLLVMType(paramType.toString()));
                }

                llvm::FunctionType *funcType = llvm::FunctionType::get(
                    getLLVMType(methodSig.returnType.toString()),
                    paramTypes,
                    false);

                // Create or get function
                llvm::Function *func = module->getFunction(funcName);
                if (!func)
                {
                    func = llvm::Function::Create(
                        funcType,
                        llvm::Function::ExternalLinkage,
                        funcName,
                        module.get());
                }

                functionMap[funcName] = func;
                // Place into slot index
                unsigned slot = methodSlotMap[className][methodSig.name];
                vtableFuncs[slot] = func;

                // Create entry block
                llvm::BasicBlock *entry = llvm::BasicBlock::Create(*context, "entry", func);
                builder->SetInsertPoint(entry);

                // For now, just return default value
                if (methodSig.returnType.getKind() == Type::Kind::UNIT)
                {
                    builder->CreateRetVoid();
                }
                else
                {
                    llvm::Type *returnType = getLLVMType(methodSig.returnType.toString());
                    llvm::Value *defaultValue = getDefaultValue(returnType);
                    builder->CreateRet(defaultValue);
                }
            }

            // Inherit missing method pointers from ancestors
            for (size_t i = 0; i < vtableFuncs.size(); ++i)
            {
                if (!vtableFuncs[i])
                {
                    const std::string &mname = vtableOrderMap[className][i];
                    // Walk up parents to find implementation
                    std::string cur = classInfo.parent;
                    while (!cur.empty())
                    {
                        auto itc = classes.find(cur);
                        if (itc == classes.end())
                            break;
                        if (itc->second.methods.count(mname))
                        {
                            std::string fname = cur + "_" + mname;
                            if (auto *f = module->getFunction(fname))
                            {
                                vtableFuncs[i] = f;
                            }
                            break;
                        }
                        if (itc->second.parent == cur)
                            break;
                        cur = itc->second.parent;
                    }
                }
            }

            // Initialize vtable contents for this class
            auto vgIt = vtableGlobals.find(className);
            auto vtTyIt = vtableTypeMap.find(className);
            if (vgIt != vtableGlobals.end() && vtTyIt != vtableTypeMap.end())
            {
                // Cast functions to slot types and fill nullptrs
                std::vector<llvm::Constant *> elems;
                auto vt = vtTyIt->second;
                for (size_t i = 0; i < vtableOrderMap[className].size(); ++i)
                {
                    llvm::Type *slotTy = vt->getElementType(i);
                    if (!vtableFuncs[i])
                    {
                        elems.push_back(llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(slotTy)));
                    }
                    else
                    {
                        llvm::Constant *c = llvm::cast<llvm::Constant>(vtableFuncs[i]);
                        if (c->getType() != slotTy)
                            c = llvm::ConstantExpr::getBitCast(c, slotTy);
                        elems.push_back(c);
                    }
                }
                llvm::Constant *vtableConst = llvm::ConstantStruct::get(vt, elems);
                vgIt->second->setInitializer(vtableConst);
            }
        }
    }

    void CodeGenerator::generateMainFunction(SemanticAnalyzer *semanticAnalyzer)
    {
        (void)semanticAnalyzer; // unused for now
        // Create main function
        llvm::FunctionType *mainType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(*context), // Return type
            false                             // Not vararg
        );

        llvm::Function *mainFunc = llvm::Function::Create(
            mainType,
            llvm::Function::ExternalLinkage,
            "main",
            module.get());

        // Create entry block
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(*context, "entry", mainFunc);
        builder->SetInsertPoint(entry);

        // new_Main and invoke main method of Main if available via dynamic dispatch
        llvm::Value *retVal = nullptr;
        llvm::Function *newMain = module->getFunction("new_Main");
        if (newMain)
        {
            auto obj = builder->CreateCall(newMain, {});
            // Load vtable and call slot for method 'main' (no args)
            auto zero32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
            auto vtp = builder->CreateGEP(classTypeMap["Main"], obj, {zero32, zero32});
            auto vt = builder->CreateLoad(llvm::PointerType::get(vtableTypeMap["Main"], 0), vtp);
            // Find slot of 'main'
            unsigned slot = 0;
            if (methodSlotMap.count("Main") && methodSlotMap["Main"].count("main"))
                slot = methodSlotMap["Main"]["main"];
            auto mptrp = builder->CreateGEP(vtableTypeMap["Main"], vt, {zero32, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), slot)});
            // Build function type: i32 (Main*)
            auto fty = llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), {llvm::PointerType::get(classTypeMap["Main"], 0)}, false);
            auto mptr = builder->CreateLoad(llvm::PointerType::get(fty, 0), mptrp);
            retVal = builder->CreateCall(fty, mptr, {obj});
        }
        if (!retVal)
        {
            retVal = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
        }
        builder->CreateRet(retVal);
    }

    bool CodeGenerator::writeToFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            return false;
        }

        file << irString;
        file.close();
        return true;
    }

    std::string CodeGenerator::getIRString() const
    {
        return irString;
    }

    // Helper method to get default values for types
    llvm::Value *CodeGenerator::getDefaultValue(llvm::Type *type)
    {
        if (type->isIntegerTy(32))
        {
            return llvm::ConstantInt::get(type, 0);
        }
        else if (type->isIntegerTy(1))
        {
            return llvm::ConstantInt::get(type, 0);
        }
        else if (type->isPointerTy())
        {
            // For any pointer type, return null
            return llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(type));
        }
        else
        {
            return llvm::UndefValue::get(type);
        }
    }

    // AST visitor methods - these will be implemented based on the AST structure
    llvm::Value *CodeGenerator::visitProgram(ProgramAst *program)
    {
        if (!program)
            return nullptr;
        llvm::Value *last = nullptr;
        for (auto *cls : program->classes)
        {
            last = visitClass(cls);
        }
        return last;
    }

    llvm::Value *CodeGenerator::visitClass(ClassAst *classAst)
    {
        if (!classAst)
            return nullptr;

        // Ensure LLVM struct types exist
        if (!classTypeMap.count(classAst->name))
            classTypeMap[classAst->name] = llvm::StructType::create(*context, classAst->name);
        if (!vtableTypeMap.count(classAst->name))
            vtableTypeMap[classAst->name] = llvm::StructType::create(*context, std::string("struct.") + classAst->name + "VTable");

        // Track current class context
        std::string prevClass = currentClass;
        llvm::Type *prevSelfTy = currentSelfType;
        currentClass = classAst->name;
        currentSelfType = llvm::PointerType::get(classTypeMap[currentClass], 0);

        // Visit fields and methods (note: actual layout/IR is built elsewhere; this is best-effort)
        for (auto *f : classAst->fields)
            visitField(f);
        for (auto *m : classAst->methods)
            visitMethod(m);

        // Restore
        currentClass = prevClass;
        currentSelfType = prevSelfTy;
        return nullptr;
    }

    llvm::Value *CodeGenerator::visitMethod(MethodAst *methodAst)
    {
        if (!methodAst || currentClass.empty())
            return nullptr;

        // Build or get function declaration
        std::string funcName = currentClass + "_" + methodAst->name;
        llvm::FunctionType *fty = getFunctionType(methodAst);
        if (!fty)
            return nullptr;

        llvm::Function *fn = module->getFunction(funcName);
        if (!fn)
        {
            fn = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, funcName, module.get());
        }

        // If function already has a body, don't re-generate
        if (!fn->empty())
            return fn;

        // Name arguments: first is self, then formals
        {
            auto it = fn->arg_begin();
            if (it != fn->arg_end())
            {
                it->setName("self");
                ++it;
            }
            for (auto *formal : methodAst->formals)
            {
                if (it == fn->arg_end())
                    break;
                it->setName(formal->name);
                ++it;
            }
        }

        // Create entry block and set insertion point
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(*context, "entry", fn);
        builder->SetInsertPoint(entry);

        // Scope for locals and map parameters to allocas
        llvm::Function *prevFunction = currentFunction;
        currentFunction = fn;
        pushScope();

        // Create allocas in entry for parameters (skip self)
        {
            auto it = fn->arg_begin();
            // Keep pointer to self as-is; no local alloca required for self
            if (it != fn->arg_end())
                ++it;
            for (auto *formal : methodAst->formals)
            {
                if (it == fn->arg_end())
                    break;
                llvm::Type *pty = getLLVMType(formal->type);
                llvm::Value *alloca = createAlloca(pty, formal->name);
                builder->CreateStore(&*it, alloca);
                setLocal(formal->name, alloca);
                ++it;
            }
        }

        // Generate body and return
        llvm::Value *retV = nullptr;
        if (methodAst->body)
            retV = visitExpression(methodAst->body);

        // Create appropriate return
        if (methodAst->returnType == "unit")
        {
            builder->CreateRetVoid();
        }
        else
        {
            llvm::Type *expected = getLLVMType(methodAst->returnType);
            if (!retV)
                retV = getDefaultValue(expected);
            // Best-effort cast if needed (no-op for now)
            if (retV->getType() != expected)
            {
                // In VSOP, types should already match post-semantics; fall back to bitcast if both are pointers
                if (retV->getType()->isPointerTy() && expected->isPointerTy())
                    retV = builder->CreateBitCast(retV, expected);
            }
            builder->CreateRet(retV);
        }

        popScope();
        currentFunction = prevFunction;
        return fn;
    }

    llvm::Value *CodeGenerator::visitField(FieldAst *fieldAst)
    {
        if (!fieldAst)
            return nullptr;
        // Field codegen is handled in init_ functions elsewhere. If an initializer exists and
        // we're inside a function with a valid builder position and class context, we could
        // initialize here; otherwise, no-op.
        return nullptr;
    }

    llvm::Value *CodeGenerator::visitExpression(ExprAst *expr)
    {
        if (!expr)
            return nullptr;
        if (auto *b = dynamic_cast<BlockExprAst *>(expr))
            return visitBlock(b);
        if (auto *i = dynamic_cast<IntegerLiteralExprAst *>(expr))
            return visitInteger(i);
        if (auto *s = dynamic_cast<StringLiteralExprAst *>(expr))
            return visitString(s);
        if (auto *bo = dynamic_cast<BooleanLiteralExprAst *>(expr))
            return visitBoolean(bo);
        if (auto *id = dynamic_cast<ObjectIdExprAst *>(expr))
            return visitIdentifier(id);
        if (auto *nf = dynamic_cast<NewExprAst *>(expr))
            return visitNew(nf);
        if (auto *as = dynamic_cast<AssignExprAst *>(expr))
            return visitAssign(as);
        if (auto *iff = dynamic_cast<IfExprAst *>(expr))
            return visitIf(iff);
        if (auto *wh = dynamic_cast<WhileExprAst *>(expr))
            return visitWhile(wh);
        if (auto *let = dynamic_cast<LetExprAst *>(expr))
            return visitLet(let);
        if (auto *call = dynamic_cast<CallExprAst *>(expr))
            return visitCall(call);
        if (auto *u = dynamic_cast<UnaryOpExprAst *>(expr))
            return visitUnaryOp(u);
        if (auto *bin = dynamic_cast<BinaryOpExprAst *>(expr))
            return visitBinaryOp(bin);
        return nullptr;
    }

    llvm::Value *CodeGenerator::visitBinaryOp(BinaryOpExprAst *binOp)
    {
        auto L = visitExpression(binOp->left);
        auto R = visitExpression(binOp->right);
        const std::string &op = binOp->op;
        if (op == "+")
            return builder->CreateAdd(L, R);
        if (op == "-")
            return builder->CreateSub(L, R);
        if (op == "*")
            return builder->CreateMul(L, R);
        if (op == "/")
            return builder->CreateSDiv(L, R);
        if (op == "=")
            return builder->CreateICmpEQ(L, R);
        if (op == "<")
            return builder->CreateICmpSLT(L, R);
        if (op == "<=")
            return builder->CreateICmpSLE(L, R);
        if (op == "and")
            return builder->CreateAnd(L, R);
        if (op == "or")
            return builder->CreateOr(L, R);
        return nullptr;
    }

    llvm::Value *CodeGenerator::visitUnaryOp(UnaryOpExprAst *unOp)
    {
        auto V = visitExpression(unOp->expr);
        if (unOp->op == "not")
        {
            return builder->CreateICmpEQ(V, llvm::ConstantInt::get(V->getType(), 0));
        }
        if (unOp->op == "-")
        {
            return builder->CreateNeg(V);
        }
        if (unOp->op == "isnull")
        {
            if (!V->getType()->isPointerTy())
                return llvm::ConstantInt::getFalse(*context);
            auto zero = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(V->getType()));
            return builder->CreateICmpEQ(V, zero);
        }
        return nullptr;
    }

    llvm::Value *CodeGenerator::visitCall(CallExprAst *call)
    {
        // Dynamic dispatch via vtable
        auto obj = visitExpression(call->object);
        // Determine static class from the expression type if available, fallback to currentClass
        std::string recvClass = currentClass;
        if (call->object && call->object->hasTypeInfo())
            recvClass = call->object->getType();
        // Load vtable
        auto zero32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
        auto vtp = builder->CreateGEP(classTypeMap[recvClass], obj, {zero32, zero32});
        auto vt = builder->CreateLoad(llvm::PointerType::get(vtableTypeMap[recvClass], 0), vtp);
        // Find slot for method
        unsigned slot = 0;
        if (methodSlotMap.count(recvClass) && methodSlotMap[recvClass].count(call->methodName))
            slot = methodSlotMap[recvClass][call->methodName];
        auto mptrp = builder->CreateGEP(vtableTypeMap[recvClass], vt, {zero32, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), slot)});

        // Build function type
        std::vector<llvm::Type *> params;
        params.push_back(llvm::PointerType::get(classTypeMap[recvClass], 0));
        // Use semantic info from vtable layout: we can't access it here directly, approximate from argument LLVM values
        std::vector<llvm::Value *> args;
        args.push_back(obj);
        for (auto *a : call->arguments)
        {
            auto av = visitExpression(a);
            args.push_back(av);
            params.push_back(av->getType());
        }
        // Return type: if annotated on call expr, use it
        llvm::Type *retTy = llvm::Type::getVoidTy(*context);
        if (call->hasTypeInfo())
            retTy = getLLVMType(call->getType());
        auto fty = llvm::FunctionType::get(retTy, params, false);
        auto mptr = builder->CreateLoad(llvm::PointerType::get(fty, 0), mptrp);
        return builder->CreateCall(fty, mptr, args);
    }

    llvm::Value *CodeGenerator::visitNew(NewExprAst *newAst)
    {
        // Call new_Class helper if available else allocate
        if (auto *nf = module->getFunction("new_" + newAst->typeName))
            return builder->CreateCall(nf, {});
        // Fallback allocation
        auto ct = classTypeMap[newAst->typeName];
        auto nullPtr = llvm::ConstantPointerNull::get(llvm::PointerType::get(ct, 0));
        auto one32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1);
        auto szPtr = builder->CreateGEP(ct, nullPtr, {one32});
        auto szInt = builder->CreatePtrToInt(szPtr, llvm::Type::getInt64Ty(*context));
        auto m = getOrCreateMalloc();
        auto raw = builder->CreateCall(m, {szInt});
        auto obj = builder->CreateBitCast(raw, llvm::PointerType::get(ct, 0));
        return obj;
    }

    llvm::Value *CodeGenerator::visitIdentifier(ObjectIdExprAst *id)
    {
        // Variables: look up in local scope map (alloca pointer)
        if (auto ptr = getLocal(id->name))
        {
            // If type annotated, use it for load element type
            llvm::Type *elemTy = nullptr;
            if (id->hasTypeInfo())
                elemTy = getLLVMType(id->getType());
            if (!elemTy)
                elemTy = llvm::Type::getInt32Ty(*context);
            return builder->CreateLoad(elemTy, ptr);
        }
        // Otherwise, could be a field: load from self
        if (!currentClass.empty())
        {
            // Assume 'self' is the first argument of current function
            if (currentFunction && !currentFunction->arg_empty())
            {
                auto self = &*currentFunction->arg_begin();
                if (fieldIndexMap.count(currentClass) && fieldIndexMap[currentClass].count(id->name))
                {
                    auto idx = fieldIndexMap[currentClass][id->name];
                    auto zero32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
                    auto gep = builder->CreateGEP(classTypeMap[currentClass], self, {zero32, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), idx)});
                    llvm::Type *elemTy = nullptr;
                    if (id->hasTypeInfo())
                        elemTy = getLLVMType(id->getType());
                    if (!elemTy)
                        elemTy = llvm::Type::getInt32Ty(*context);
                    return builder->CreateLoad(elemTy, gep);
                }
            }
        }
        return nullptr;
    }

    llvm::Value *CodeGenerator::visitInteger(IntegerLiteralExprAst *integer)
    {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), integer->value);
    }

    llvm::Value *CodeGenerator::visitString(StringLiteralExprAst *string)
    {
        return builder->CreateGlobalString(string->value);
    }

    llvm::Value *CodeGenerator::visitBoolean(BooleanLiteralExprAst *boolean)
    {
        return llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context), boolean->value ? 1 : 0);
    }

    llvm::Value *CodeGenerator::visitBlock(BlockExprAst *block)
    {
        llvm::Value *last = nullptr;
        for (auto *e : block->expressions)
            last = visitExpression(e);
        return last;
    }

    llvm::Value *CodeGenerator::visitIf(IfExprAst *ifAst)
    {
        auto cond = visitExpression(ifAst->condition);
        // Normalize bool to i1 if needed
        if (!cond->getType()->isIntegerTy(1))
            cond = builder->CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0));

        llvm::Function *fn = builder->GetInsertBlock()->getParent();
        auto thenBB = llvm::BasicBlock::Create(*context, "then", fn);
        auto elseBB = llvm::BasicBlock::Create(*context, "else", fn);
        auto mergeBB = llvm::BasicBlock::Create(*context, "ifend", fn);

        builder->CreateCondBr(cond, thenBB, elseBB);

        // Then block
        builder->SetInsertPoint(thenBB);
        auto thenV = visitExpression(ifAst->thenExpr);
        auto thenEndBB = builder->GetInsertBlock();
        builder->CreateBr(mergeBB);

        // Else block
        builder->SetInsertPoint(elseBB);
        llvm::Value *elseV = nullptr;
        if (ifAst->elseExpr)
            elseV = visitExpression(ifAst->elseExpr);
        auto elseEndBB = builder->GetInsertBlock();
        builder->CreateBr(mergeBB);

        // Merge
        builder->SetInsertPoint(mergeBB);

        // If expression has a type -> create phi
        if (ifAst->hasTypeInfo() && ifAst->getType() != "unit")
        {
            llvm::Type *ty = getLLVMType(ifAst->getType());
            auto phi = builder->CreatePHI(ty, 2);
            if (thenV)
                phi->addIncoming(thenV, thenEndBB);
            if (elseV)
                phi->addIncoming(elseV, elseEndBB);
            return phi;
        }
        return nullptr;
    }

    llvm::Value *CodeGenerator::visitWhile(WhileExprAst *whileAst)
    {
        llvm::Function *fn = builder->GetInsertBlock()->getParent();
        auto condBB = llvm::BasicBlock::Create(*context, "while.cond", fn);
        auto bodyBB = llvm::BasicBlock::Create(*context, "while.body", fn);
        auto endBB = llvm::BasicBlock::Create(*context, "while.end", fn);

        builder->CreateBr(condBB);
        builder->SetInsertPoint(condBB);
        auto cond = visitExpression(whileAst->condition);
        if (!cond->getType()->isIntegerTy(1))
            cond = builder->CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0));
        builder->CreateCondBr(cond, bodyBB, endBB);

        builder->SetInsertPoint(bodyBB);
        visitExpression(whileAst->body);
        builder->CreateBr(condBB);

        builder->SetInsertPoint(endBB);
        return nullptr; // unit
    }

    llvm::Value *CodeGenerator::visitLet(LetExprAst *letAst)
    {
        pushScope();
        // Allocate local variable
        llvm::Type *ty = getLLVMType(letAst->type);
        auto *alloca = createAlloca(ty, letAst->name);
        setLocal(letAst->name, alloca);
        // Initialize
        llvm::Value *initV = nullptr;
        if (letAst->initExpr)
            initV = visitExpression(letAst->initExpr);
        if (!initV)
            initV = getDefaultValue(ty);
        builder->CreateStore(initV, alloca);
        // Scope expr
        auto result = visitExpression(letAst->scopeExpr);
        popScope();
        return result;
    }

    llvm::Value *CodeGenerator::visitAssign(AssignExprAst *assign)
    {
        auto rhs = visitExpression(assign->expr);
        // Local variable?
        if (auto ptr = getLocal(assign->name))
        {
            builder->CreateStore(rhs, ptr);
            return rhs;
        }
        // Field of self
        if (!currentClass.empty() && currentFunction && !currentFunction->arg_empty())
        {
            if (fieldIndexMap.count(currentClass) && fieldIndexMap[currentClass].count(assign->name))
            {
                auto self = &*currentFunction->arg_begin();
                auto idx = fieldIndexMap[currentClass][assign->name];
                auto zero32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
                auto gep = builder->CreateGEP(classTypeMap[currentClass], self, {zero32, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), idx)});
                builder->CreateStore(rhs, gep);
                return rhs;
            }
        }
        return rhs;
    }

    // Utility methods
    llvm::Type *CodeGenerator::getLLVMType(const std::string &vsopType)
    {
        auto it = typeMap.find(vsopType);
        if (it != typeMap.end())
        {
            return it->second;
        }

        // Check if it's a class type
        auto classIt = classTypeMap.find(vsopType);
        if (classIt != classTypeMap.end())
        {
            return llvm::PointerType::get(classIt->second, 0);
        }

        // Default to i32 if type not found
        return llvm::Type::getInt32Ty(*context);
    }

    llvm::FunctionType *CodeGenerator::getFunctionType(MethodAst *method)
    {
        if (!method)
            return nullptr;
        // First parameter is 'self' of current class
        llvm::Type *selfPtrTy = nullptr;
        if (!currentClass.empty() && classTypeMap.count(currentClass))
            selfPtrTy = llvm::PointerType::get(classTypeMap[currentClass], 0);
        else if (currentSelfType)
            selfPtrTy = currentSelfType;
        else
            return nullptr;

        std::vector<llvm::Type *> params;
        params.push_back(selfPtrTy);
        for (auto *formal : method->formals)
        {
            params.push_back(getLLVMType(formal->type));
        }
        llvm::Type *retTy = getLLVMType(method->returnType);
        return llvm::FunctionType::get(retTy, params, false);
    }

    llvm::Value *CodeGenerator::createAlloca(llvm::Type *type, const std::string &name)
    {
        llvm::BasicBlock *entry = &currentFunction->getEntryBlock();
        llvm::IRBuilder<> tempBuilder(entry, entry->begin());
        return tempBuilder.CreateAlloca(type, nullptr, name);
    }

    void CodeGenerator::createReturn(llvm::Value *value)
    {
        if (value)
        {
            builder->CreateRet(value);
        }
        else
        {
            builder->CreateRetVoid();
        }
    }

    llvm::Value *CodeGenerator::createLoad(llvm::Value *ptr, llvm::Type *elemType)
    {
        return builder->CreateLoad(elemType, ptr);
    }

    void CodeGenerator::createStore(llvm::Value *value, llvm::Value *ptr)
    {
        builder->CreateStore(value, ptr);
    }

    llvm::Value *CodeGenerator::createGEP(llvm::Type *elemType, llvm::Value *ptr, llvm::Value *index)
    {
        return builder->CreateGEP(elemType, ptr, {index});
    }

    llvm::Value *CodeGenerator::createCast(llvm::Value *value, llvm::Type *targetType)
    {
        if (value->getType() == targetType)
        {
            return value;
        }

        // Add basic casting logic here
        return value;
    }

    llvm::Constant *CodeGenerator::getZeroInitializer(llvm::Type *type)
    {
        if (type->isIntegerTy())
            return llvm::ConstantInt::get(type, 0);
        if (type->isPointerTy())
            return llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(type));
        if (type->isStructTy())
            return llvm::ConstantAggregateZero::get(type);
        if (type->isVoidTy())
            return nullptr;
        return llvm::UndefValue::get(type);
    }

    // --------- Scope helpers ---------
    void CodeGenerator::pushScope()
    {
        localVars.emplace_back();
    }

    void CodeGenerator::popScope()
    {
        if (!localVars.empty())
            localVars.pop_back();
    }

    void CodeGenerator::setLocal(const std::string &name, llvm::Value *allocaPtr)
    {
        if (localVars.empty())
            localVars.emplace_back();
        localVars.back()[name] = allocaPtr;
    }

    llvm::Value *CodeGenerator::getLocal(const std::string &name)
    {
        for (auto it = localVars.rbegin(); it != localVars.rend(); ++it)
        {
            auto f = it->find(name);
            if (f != it->end())
                return f->second;
        }
        return nullptr;
    }

    // --------- Runtime helpers ---------
    llvm::Function *CodeGenerator::getOrCreateMalloc()
    {
        if (auto *f = module->getFunction("malloc"))
            return f;
        auto retTy = llvm::PointerType::get(llvm::Type::getInt8Ty(*context), 0);
        auto fty = llvm::FunctionType::get(retTy, {llvm::Type::getInt64Ty(*context)}, false);
        return llvm::Function::Create(fty, llvm::Function::ExternalLinkage, "malloc", module.get());
    }

    llvm::Value *CodeGenerator::createNewObject(const std::string &className, llvm::IRBuilder<> &b)
    {
        auto ct = classTypeMap[className];
        auto nullPtr = llvm::ConstantPointerNull::get(llvm::PointerType::get(ct, 0));
        auto one32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 1);
        auto szPtr = b.CreateGEP(ct, nullPtr, {one32});
        auto szInt = b.CreatePtrToInt(szPtr, llvm::Type::getInt64Ty(*context));
        auto m = getOrCreateMalloc();
        auto raw = b.CreateCall(m, {szInt});
        auto obj = b.CreateBitCast(raw, llvm::PointerType::get(ct, 0));
        // init vtable field
        auto zero32 = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0);
        auto vg = vtableGlobals.find(className);
        if (vg != vtableGlobals.end())
        {
            auto vtp = b.CreateGEP(ct, obj, {zero32, zero32});
            b.CreateStore(vg->second, vtp);
        }
        return obj;
    }

    // --------- Layout helpers ---------
    void CodeGenerator::ensureEmptyTypes(const std::map<std::string, ClassInfo> &classes)
    {
        for (const auto &p : classes)
        {
            const std::string &className = p.first;
            if (!classTypeMap.count(className))
                classTypeMap[className] = llvm::StructType::create(*context, className);
            std::string vtableName = std::string("struct.") + className + "VTable";
            if (!vtableTypeMap.count(className))
                vtableTypeMap[className] = llvm::StructType::create(*context, vtableName);
        }
    }

    std::vector<std::pair<std::string, llvm::Type *>> CodeGenerator::getInheritedFields(const std::string &className, const std::map<std::string, ClassInfo> &classes)
    {
        std::vector<std::pair<std::string, llvm::Type *>> res;
        const auto it = classes.find(className);
        if (it == classes.end())
            return res;
        const auto &ci = it->second;
        if (ci.parent != "Object" && classes.count(ci.parent))
        {
            auto parentFields = getInheritedFields(ci.parent, classes);
            res.insert(res.end(), parentFields.begin(), parentFields.end());
        }
        // Append own fields
        for (const auto &fp : ci.fields)
        {
            res.emplace_back(fp.first, getLLVMType(fp.second.toString()));
        }
        return res;
    }

    void CodeGenerator::buildClassFieldLayout(const std::string &className, const std::map<std::string, ClassInfo> &classes)
    {
        // If already built, skip
        if (fieldOrderMap.count(className))
            return;
        const auto it = classes.find(className);
        if (it == classes.end())
            return;
        // Ensure parent first
        const std::string &parent = it->second.parent;
        if (parent != "Object" && classes.count(parent))
            buildClassFieldLayout(parent, classes);

        // Build ordered fields: inherited + own
        std::vector<std::string> order;
        std::map<std::string, unsigned> index;
        std::vector<llvm::Type *> bodyTypes;

        // First vtable pointer
        bodyTypes.push_back(llvm::PointerType::get(vtableTypeMap[className], 0));

        unsigned idx = 1;
        if (parent != "Object" && fieldOrderMap.count(parent))
        {
            // Copy parent's order and types by introspecting parent class type
            for (const auto &fname : fieldOrderMap[parent])
            {
                order.push_back(fname);
                index[fname] = idx++;
            }
            // Parent body types are already in parent class type: replicate here for alignment
            auto pty = classTypeMap[parent];
            // pty layout: [vtable, parent fields...]; we need only fields after vtable
            for (unsigned i = 1; i < pty->getNumElements(); ++i)
            {
                bodyTypes.push_back(pty->getElementType(i));
            }
        }

        // Own fields
        for (const auto &fp : it->second.fields)
        {
            order.push_back(fp.first);
            index[fp.first] = idx++;
            bodyTypes.push_back(getLLVMType(fp.second.toString()));
        }

        fieldOrderMap[className] = order;
        fieldIndexMap[className] = index;
        // Set class body
        classTypeMap[className]->setBody(bodyTypes);
    }

    std::vector<std::string> CodeGenerator::getInheritedMethods(const std::string &className, const std::map<std::string, ClassInfo> &classes)
    {
        std::vector<std::string> res;
        const auto it = classes.find(className);
        if (it == classes.end())
            return res;
        const auto &ci = it->second;
        if (ci.parent != "Object" && classes.count(ci.parent))
        {
            res = getInheritedMethods(ci.parent, classes);
        }
        // Add/override with own methods: maintain stable order, overriding replaces slot
        for (const auto &mp : ci.methods)
        {
            const std::string &m = mp.first;
            auto pos = std::find(res.begin(), res.end(), m);
            if (pos == res.end())
                res.push_back(m);
            else
                *pos = m; // override keeps position
        }
        return res;
    }

    void CodeGenerator::buildClassVTableLayout(const std::string &className, const std::map<std::string, ClassInfo> &classes)
    {
        if (vtableOrderMap.count(className))
            return;
        const auto it = classes.find(className);
        if (it == classes.end())
            return;
        // Ensure parent first
        const std::string &parent = it->second.parent;
        if (parent != "Object" && classes.count(parent))
            buildClassVTableLayout(parent, classes);

        auto order = getInheritedMethods(className, classes);
        vtableOrderMap[className] = order;
        std::map<std::string, unsigned> slots;
        for (unsigned i = 0; i < order.size(); ++i)
            slots[order[i]] = i;
        methodSlotMap[className] = slots;
    }
}
