/**
 * @brief LLVM IR code generator implementation for VSOP compiler
 */

#include "codegen.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

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
        typeMap["string"] = llvm::Type::getInt8PtrTy(*context);
        typeMap["unit"] = llvm::Type::getVoidTy(*context);
    }

    std::string CodeGenerator::generateCode(SemanticAnalyzer* semanticAnalyzer)
    {
        if (!semanticAnalyzer) {
            return "";
        }

        try {
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
        catch (const std::exception& e) {
            std::cerr << "Error during code generation: " << e.what() << std::endl;
            return "";
        }
    }

    void CodeGenerator::generateClassTypes(SemanticAnalyzer* semanticAnalyzer)
    {
        // Get class information from semantic analyzer
        const auto& classes = semanticAnalyzer->getClasses();
        
        for (const auto& classPair : classes) {
            const std::string& className = classPair.first;
            const ClassInfo& classInfo = classPair.second;
            
            // Create class structure type
            std::vector<llvm::Type*> fieldTypes;
            
            // First field is always the vtable pointer
            std::string vtableName = "struct." + className + "VTable";
            llvm::StructType* vtableType = llvm::StructType::create(*context, vtableName);
            vtableTypeMap[className] = vtableType;
            fieldTypes.push_back(vtableType->getPointerTo());
            
            // Add field types
            for (const auto& fieldPair : classInfo.fields) {
                const Type& fieldType = fieldPair.second;
                fieldTypes.push_back(getLLVMType(fieldType.toString()));
            }
            
            // Create the class structure
            llvm::StructType* classType = llvm::StructType::create(*context, className);
            classType->setBody(fieldTypes);
            classTypeMap[className] = classType;
        }
    }

    void CodeGenerator::generateVTableTypes(SemanticAnalyzer* semanticAnalyzer)
    {
        const auto& classes = semanticAnalyzer->getClasses();
        
        for (const auto& classPair : classes) {
            const std::string& className = classPair.first;
            const ClassInfo& classInfo = classPair.second;
            
            // Get vtable type
            auto vtableIt = vtableTypeMap.find(className);
            if (vtableIt == vtableTypeMap.end()) continue;
            
            llvm::StructType* vtableType = vtableIt->second;
            
            // Create vtable structure with method pointers
            std::vector<llvm::Type*> vtableFields;
            
            for (const auto& methodPair : classInfo.methods) {
                const MethodSignature& methodSig = methodPair.second;
                
                // Create function type for this method
                std::vector<llvm::Type*> paramTypes;
                paramTypes.push_back(classTypeMap[className]->getPointerTo()); // self parameter
                
                for (const Type& paramType : methodSig.parameterTypes) {
                    paramTypes.push_back(getLLVMType(paramType.toString()));
                }
                
                llvm::FunctionType* funcType = llvm::FunctionType::get(
                    getLLVMType(methodSig.returnType.toString()),
                    paramTypes,
                    false
                );
                
                vtableFields.push_back(funcType->getPointerTo());
            }
            
            if (!vtableFields.empty()) {
                vtableType->setBody(vtableFields);
            }
        }
    }

    void CodeGenerator::generateGlobalVariables(SemanticAnalyzer* semanticAnalyzer)
    {
        // Generate vtable global variables
        const auto& classes = semanticAnalyzer->getClasses();
        
        for (const auto& classPair : classes) {
            const std::string& className = classPair.first;
            const ClassInfo& classInfo = classPair.second;
            
            // Create vtable global variable
            std::string vtableName = className + "_vtable";
            auto vtableIt = vtableTypeMap.find(className);
            if (vtableIt != vtableTypeMap.end()) {
                llvm::GlobalVariable* vtableGlobal = new llvm::GlobalVariable(
                    *module,
                    vtableIt->second,
                    false, // not constant
                    llvm::GlobalValue::ExternalLinkage,
                    nullptr, // initializer
                    vtableName
                );
            }
        }
    }

    void CodeGenerator::generateFunctions(SemanticAnalyzer* semanticAnalyzer)
    {
        const auto& classes = semanticAnalyzer->getClasses();
        
        for (const auto& classPair : classes) {
            const std::string& className = classPair.first;
            const ClassInfo& classInfo = classPair.second;
            
            // Generate methods for this class
            for (const auto& methodPair : classInfo.methods) {
                const MethodSignature& methodSig = methodPair.second;
                
                // Create function name: ClassName_methodName
                std::string funcName = className + "_" + methodSig.name;
                
                // Create function type
                std::vector<llvm::Type*> paramTypes;
                paramTypes.push_back(classTypeMap[className]->getPointerTo()); // self parameter
                
                for (const Type& paramType : methodSig.parameterTypes) {
                    paramTypes.push_back(getLLVMType(paramType.toString()));
                }
                
                llvm::FunctionType* funcType = llvm::FunctionType::get(
                    getLLVMType(methodSig.returnType.toString()),
                    paramTypes,
                    false
                );
                
                // Create function
                llvm::Function* func = llvm::Function::Create(
                    funcType,
                    llvm::Function::ExternalLinkage,
                    funcName,
                    module.get()
                );
                
                functionMap[funcName] = func;
                
                // Create entry block
                llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", func);
                builder->SetInsertPoint(entry);
                
                // For now, just return default value
                if (methodSig.returnType.getKind() == Type::Kind::UNIT) {
                    builder->CreateRetVoid();
                } else {
                    llvm::Type* returnType = getLLVMType(methodSig.returnType.toString());
                    llvm::Value* defaultValue = getDefaultValue(returnType);
                    builder->CreateRet(defaultValue);
                }
            }
        }
    }

    void CodeGenerator::generateMainFunction(SemanticAnalyzer* semanticAnalyzer)
    {
        // Create main function
        llvm::FunctionType* mainType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(*context),  // Return type
            false  // Not vararg
        );
        
        llvm::Function* mainFunc = llvm::Function::Create(
            mainType,
            llvm::Function::ExternalLinkage,
            "main",
            module.get()
        );
        
        // Create entry block
        llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", mainFunc);
        builder->SetInsertPoint(entry);
        
        // For now, just return 0
        builder->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 0));
    }

    bool CodeGenerator::writeToFile(const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open()) {
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
    llvm::Value* CodeGenerator::getDefaultValue(llvm::Type* type)
    {
        if (type->isIntegerTy(32)) {
            return llvm::ConstantInt::get(type, 0);
        } else if (type->isIntegerTy(1)) {
            return llvm::ConstantInt::get(type, 0);
        } else if (type->isPointerTy() && type->getPointerElementType()->isIntegerTy(8)) {
            return llvm::ConstantPointerNull::get(type);
        } else {
            return llvm::UndefValue::get(type);
        }
    }

    // AST visitor methods - these will be implemented based on the AST structure
    llvm::Value* CodeGenerator::visitProgram(ProgramAst* program)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitClass(ClassAst* classAst)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitMethod(MethodAst* methodAst)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitField(FieldAst* fieldAst)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitExpression(ExpressionAst* expr)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitBinaryOp(BinaryOpAst* binOp)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitUnaryOp(UnaryOpAst* unOp)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitCall(CallAst* call)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitNew(NewAst* newAst)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitIdentifier(IdentifierAst* id)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitInteger(IntegerAst* integer)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitString(StringAst* string)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitBoolean(BooleanAst* boolean)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitBlock(BlockAst* block)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitIf(IfAst* ifAst)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitWhile(WhileAst* whileAst)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitLet(LetAst* letAst)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    llvm::Value* CodeGenerator::visitAssign(AssignAst* assign)
    {
        // Implementation will be added based on AST structure
        return nullptr;
    }

    // Utility methods
    llvm::Type* CodeGenerator::getLLVMType(const std::string& vsopType)
    {
        auto it = typeMap.find(vsopType);
        if (it != typeMap.end()) {
            return it->second;
        }
        
        // Check if it's a class type
        auto classIt = classTypeMap.find(vsopType);
        if (classIt != classTypeMap.end()) {
            return classIt->second->getPointerTo();
        }
        
        // Default to i32 if type not found
        return llvm::Type::getInt32Ty(*context);
    }

    llvm::FunctionType* CodeGenerator::getFunctionType(MethodAst* method)
    {
        // This will be implemented based on the method signature
        return nullptr;
    }

    llvm::Value* CodeGenerator::createAlloca(llvm::Type* type, const std::string& name)
    {
        llvm::BasicBlock* entry = &currentFunction->getEntryBlock();
        llvm::IRBuilder<> tempBuilder(entry, entry->begin());
        return tempBuilder.CreateAlloca(type, nullptr, name);
    }

    void CodeGenerator::createReturn(llvm::Value* value)
    {
        if (value) {
            builder->CreateRet(value);
        } else {
            builder->CreateRetVoid();
        }
    }

    llvm::Value* CodeGenerator::createLoad(llvm::Value* ptr)
    {
        return builder->CreateLoad(ptr->getType()->getPointerElementType(), ptr);
    }

    void CodeGenerator::createStore(llvm::Value* value, llvm::Value* ptr)
    {
        builder->CreateStore(value, ptr);
    }

    llvm::Value* CodeGenerator::createGEP(llvm::Value* ptr, llvm::Value* index)
    {
        return builder->CreateGEP(ptr->getType()->getPointerElementType(), ptr, index);
    }

    llvm::Value* CodeGenerator::createCast(llvm::Value* value, llvm::Type* targetType)
    {
        if (value->getType() == targetType) {
            return value;
        }
        
        // Add basic casting logic here
        return value;
    }
}
