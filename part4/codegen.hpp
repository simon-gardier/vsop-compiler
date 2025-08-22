/**
 * @brief LLVM IR code generator for VSOP compiler
 */

#ifndef _CODEGEN_HPP
#define _CODEGEN_HPP

#include <memory>
#include <string>
#include <map>
#include <vector>

// LLVM includes - using more standard paths
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
#include "llvm/IR/StructType.h"

// Alternative include paths if the above don't work
#ifdef LLVM_ALTERNATIVE_INCLUDES
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/IRBuilder.h"
#include "llvm/Function.h"
#include "llvm/Type.h"
#include "llvm/Value.h"
#include "llvm/Constants.h"
#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/GlobalVariable.h"
#include "llvm/StructType.h"
#endif

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
        std::string generateCode(SemanticAnalyzer* semanticAnalyzer);

        /**
         * @brief Write the generated LLVM IR to a file.
         *
         * @param filename The output filename.
         * @return true if successful, false otherwise.
         */
        bool writeToFile(const std::string& filename);

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
        std::map<std::string, llvm::Type*> typeMap;
        std::map<std::string, llvm::StructType*> classTypeMap;
        std::map<std::string, llvm::StructType*> vtableTypeMap;

        // Function mappings
        std::map<std::string, llvm::Function*> functionMap;

        // Current function and basic block
        llvm::Function* currentFunction;
        llvm::BasicBlock* currentBlock;

        // Helper methods
        void initializeTypes();
        void generateClassTypes(SemanticAnalyzer* semanticAnalyzer);
        void generateVTableTypes(SemanticAnalyzer* semanticAnalyzer);
        void generateGlobalVariables(SemanticAnalyzer* semanticAnalyzer);
        void generateFunctions(SemanticAnalyzer* semanticAnalyzer);
        void generateMainFunction(SemanticAnalyzer* semanticAnalyzer);

        // AST visitor methods
        llvm::Value* visitProgram(ProgramAst* program);
        llvm::Value* visitClass(ClassAst* classAst);
        llvm::Value* visitMethod(MethodAst* methodAst);
        llvm::Value* visitField(FieldAst* fieldAst);
        llvm::Value* visitExpression(ExpressionAst* expr);
        llvm::Value* visitBinaryOp(BinaryOpAst* binOp);
        llvm::Value* visitUnaryOp(UnaryOpAst* unOp);
        llvm::Value* visitCall(CallAst* call);
        llvm::Value* visitNew(NewAst* newAst);
        llvm::Value* visitIdentifier(IdentifierAst* id);
        llvm::Value* visitInteger(IntegerAst* integer);
        llvm::Value* visitString(StringAst* string);
        llvm::Value* visitBoolean(BooleanAst* boolean);
        llvm::Value* visitBlock(BlockAst* block);
        llvm::Value* visitIf(IfAst* ifAst);
        llvm::Value* visitWhile(WhileAst* whileAst);
        llvm::Value* visitLet(LetAst* letAst);
        llvm::Value* visitAssign(AssignAst* assign);

        // Utility methods
        llvm::Type* getLLVMType(const std::string& vsopType);
        llvm::FunctionType* getFunctionType(MethodAst* method);
        llvm::Value* createAlloca(llvm::Type* type, const std::string& name);
        void createReturn(llvm::Value* value);
        llvm::Value* createLoad(llvm::Value* ptr);
        void createStore(llvm::Value* value, llvm::Value* ptr);
        llvm::Value* createGEP(llvm::Value* ptr, llvm::Value* index);
        llvm::Value* createCast(llvm::Value* value, llvm::Type* targetType);
        llvm::Value* getDefaultValue(llvm::Type* type);
    };
}

#endif
