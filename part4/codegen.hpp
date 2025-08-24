/**
 * @brief LLVM IR code generator for VSOP compiler
 */

#ifndef _CODEGEN_HPP
#define _CODEGEN_HPP

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/GlobalVariable.h"
// For llvm::PointerType usage in signatures
#include "llvm/IR/DerivedTypes.h"

#include "ast.hpp"
#include "semantic.hpp"

namespace VSOP
{
    class CodeGenerator
    {
    public:
        /**
         * @brief Construct a new CodeGenerator.
         */
        CodeGenerator();

        /**
         * @brief Destroy the CodeGenerator.
         */
        ~CodeGenerator();

        /**
         * @brief Generate LLVM IR from the annotated AST.
         *
         * @param semanticAnalyzer The semantic analyzer containing the annotated AST.
         * @return std::string The generated LLVM IR as a string.
         */
        std::string generateCode(SemanticAnalyzer *semanticAnalyzer);

        /**
         * @brief Write the generated LLVM IR to a file.
         *
         * @param filename The output filename.
         * @return true if successful, false otherwise.
         */
        bool writeToFile(const std::string &filename);

        /**
         * @brief Get the generated LLVM IR as a string.
         *
         * @return std::string The LLVM IR.
         */
        std::string getIRString() const;

    private:
        // LLVM context and module
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;

        // Generated IR string
        std::string irString;

        // Type mappings
        std::map<std::string, llvm::Type *> typeMap;
        std::map<std::string, llvm::StructType *> classTypeMap;
        std::map<std::string, llvm::StructType *> vtableTypeMap;
        // Layout mappings
        // Field order (including inherited fields) and indices per class
        std::map<std::string, std::vector<std::string>> fieldOrderMap;
        std::map<std::string, std::map<std::string, unsigned>> fieldIndexMap;
        // VTable method order (including inherited methods) and slot indices per class
        std::map<std::string, std::vector<std::string>> vtableOrderMap;
        std::map<std::string, std::map<std::string, unsigned>> methodSlotMap;

        // Function mappings
        std::map<std::string, llvm::Function *> functionMap;
        std::map<std::string, llvm::GlobalVariable *> vtableGlobals;

        // Current function and basic block
        llvm::Function *currentFunction;
        llvm::BasicBlock *currentBlock;
        std::string currentClass;
        llvm::Type *currentSelfType = nullptr;
        std::vector<std::unordered_map<std::string, llvm::Value *>> localVars;

        // Helper methods
        void initializeTypes();
        void generateClassTypes(SemanticAnalyzer *semanticAnalyzer);
        void generateVTableTypes(SemanticAnalyzer *semanticAnalyzer);
        void generateGlobalVariables(SemanticAnalyzer *semanticAnalyzer);
        void generateFunctions(SemanticAnalyzer *semanticAnalyzer);
        void generateMainFunction(SemanticAnalyzer *semanticAnalyzer);
        // Helpers for layout construction
        void ensureEmptyTypes(const std::map<std::string, ClassInfo> &classes);
        void buildClassFieldLayout(const std::string &className, const std::map<std::string, ClassInfo> &classes);
        void buildClassVTableLayout(const std::string &className, const std::map<std::string, ClassInfo> &classes);
        std::vector<std::pair<std::string, llvm::Type *>> getInheritedFields(const std::string &className, const std::map<std::string, ClassInfo> &classes);
        std::vector<std::string> getInheritedMethods(const std::string &className, const std::map<std::string, ClassInfo> &classes);

        // AST visitor methods
        llvm::Value *visitProgram(ProgramAst *program);
        llvm::Value *visitClass(ClassAst *classAst);
        llvm::Value *visitMethod(MethodAst *methodAst);
        llvm::Value *visitField(FieldAst *fieldAst);
        llvm::Value *visitExpression(ExprAst *expr);
        llvm::Value *visitBinaryOp(BinaryOpExprAst *binOp);
        llvm::Value *visitUnaryOp(UnaryOpExprAst *unOp);
        llvm::Value *visitCall(CallExprAst *call);
        llvm::Value *visitNew(NewExprAst *newAst);
        llvm::Value *visitIdentifier(ObjectIdExprAst *id);
        llvm::Value *visitInteger(IntegerLiteralExprAst *integer);
        llvm::Value *visitString(StringLiteralExprAst *string);
        llvm::Value *visitBoolean(BooleanLiteralExprAst *boolean);
        llvm::Value *visitBlock(BlockExprAst *block);
        llvm::Value *visitSelf();
        llvm::Value *visitIf(IfExprAst *IfExprAst);
        llvm::Value *visitWhile(WhileExprAst *whileAst);
        llvm::Value *visitLet(LetExprAst *letAst);
        llvm::Value *visitAssign(AssignExprAst *assign);

        // Utility methods
        llvm::Type *getLLVMType(const std::string &vsopType);
        llvm::FunctionType *getFunctionType(MethodAst *method);
        llvm::Value *createAlloca(llvm::Type *type, const std::string &name);
        void createReturn(llvm::Value *value);
        // With opaque pointers, callers must specify the element type
        llvm::Value *createLoad(llvm::Value *ptr, llvm::Type *elemType);
        void createStore(llvm::Value *value, llvm::Value *ptr);
        // Provide element type explicitly for GEP
        llvm::Value *createGEP(llvm::Type *elemType, llvm::Value *ptr, llvm::Value *index);
        llvm::Value *createCast(llvm::Value *value, llvm::Type *targetType);
        llvm::Value *getDefaultValue(llvm::Type *type);
        llvm::Constant *getZeroInitializer(llvm::Type *type);

        // Scope helpers
        void pushScope();
        void popScope();
        void setLocal(const std::string &name, llvm::Value *allocaPtr);
        llvm::Value *getLocal(const std::string &name);

        // Runtime helpers
        llvm::Function *getOrCreateMalloc();
        llvm::Value *createNewObject(const std::string &className, llvm::IRBuilder<> &b);
    };
}

#endif
