/**
 * @brief Semantic analyzer for VSOP compiler
 */

#ifndef _SEMANTIC_HPP
#define _SEMANTIC_HPP

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "ast.hpp"

namespace VSOP
{
    /**
     * @brief Represents a type in VSOP
     */
    class Type
    {
    public:
        enum class Kind
        {
            UNIT,
            BOOL,
            INT32,
            STRING,
            CLASS,
            ERROR
        };

        Type() : kind(Kind::ERROR), className("") {}
        Type(Kind kind, const std::string &className = "")
            : kind(kind), className(className) {}

        Kind getKind() const { return kind; }
        const std::string &getClassName() const { return className; }

        std::string toString() const;

        static Type Unit() { return Type(Kind::UNIT); }
        static Type Bool() { return Type(Kind::BOOL); }
        static Type Int32() { return Type(Kind::INT32); }
        static Type String() { return Type(Kind::STRING); }
        static Type Class(const std::string &className) { return Type(Kind::CLASS, className); }
        static Type Error() { return Type(Kind::ERROR); }

        bool operator==(const Type &other) const;
        bool operator!=(const Type &other) const;

    private:
        Kind kind;
        std::string className;
    };

    /**
     * @brief Represents a method signature
     */
    struct MethodSignature
    {
        std::string name;
        std::vector<Type> parameterTypes;
        Type returnType;
        int line;
        int column;

        MethodSignature() : name(""), parameterTypes(), returnType(), line(0), column(0) {}
        MethodSignature(const std::string &name,
                        const std::vector<Type> &paramTypes,
                        const Type &retType,
                        int line = 0, int column = 0)
            : name(name), parameterTypes(paramTypes), returnType(retType),
              line(line), column(column) {}
    };

    /**
     * @brief Represents a class in the symbol table
     */
    class ClassInfo
    {
    public:
        ClassInfo() : name(""), parent(""), line(0), column(0) {}
        ClassInfo(const std::string &name, const std::string &parent = "Object")
            : name(name), parent(parent), line(0), column(0) {}

        std::string name;
        std::string parent;
        std::map<std::string, Type> fields;             // field name -> type
        std::map<std::string, MethodSignature> methods; // method name -> signature
        int line;
        int column;
    };

    /**
     * @brief Represents a scope in the symbol table
     */
    class Scope
    {
    public:
        Scope() = default;

        void addVariable(const std::string &name, const Type &type);
        Type getVariableType(const std::string &name, bool &found) const;
        bool hasVariable(const std::string &name) const;

    private:
        std::map<std::string, Type> variables;
    };

    /**
     * @brief Semantic analyzer for VSOP programs
     */
    class SemanticAnalyzer
    {
    public:
        SemanticAnalyzer(const std::string &filename) : filename(filename) {}

        /**
         * @brief Analyze the program and perform semantic checking
         *
         * @param program The AST of the program to analyze
         * @return true if no semantic errors, false otherwise
         */
        bool analyze(ProgramAst *program);

        /**
         * @brief Get the annotated AST string
         *
         * @return std::string The annotated AST string
         */
        std::string getAnnotatedString() const { return annotatedString; }

        /**
         * @brief Check if there were any semantic errors
         *
         * @return true if there were errors, false otherwise
         */
        bool hasErrors() const { return !errors.empty(); }

        /**
         * @brief Get all error messages
         *
         * @return const std::vector<std::string>& Vector of error messages
         */
        const std::vector<std::string> &getErrors() const { return errors; }

    private:
        std::string filename;
        std::vector<std::string> errors;
        std::string annotatedString;

        // Symbol tables
        std::map<std::string, ClassInfo> classes;
        std::vector<Scope> scopes;

        // Current class being analyzed
        ClassInfo *currentClass;

        // Current method being analyzed
        const MethodSignature *currentMethod;
        bool inFieldInitializer = false;    // Track if we're in a field initializer context
        bool fieldInitializerError = false; // Track if we've already reported field initializer errors

        // Helper methods
        void reportError(int line, int column, const std::string &message);
        void enterScope();
        void exitScope();
        void addVariable(const std::string &name, const Type &type);
        Type getVariableType(const std::string &name, bool &found);
        bool hasVariable(const std::string &name);

        // Type checking methods
        Type checkClass(ClassAst *classAst);
        Type checkField(FieldAst *fieldAst);
        Type checkMethod(MethodAst *methodAst);
        Type checkExpression(ExprAst *expr, const Type &expectedType = Type::Error());
        Type checkBlock(BlockExprAst *block, const Type &expectedType);
        Type checkIf(IfExprAst *ifExpr, const Type &expectedType);
        Type checkWhile(WhileExprAst *whileExpr, const Type &expectedType);
        Type checkLet(LetExprAst *letExpr, const Type &expectedType);
        Type checkAssign(AssignExprAst *assign, const Type &expectedType);
        Type checkUnaryOp(UnaryOpExprAst *unaryOp, const Type &expectedType);
        Type checkBinaryOp(BinaryOpExprAst *binaryOp, const Type &expectedType);
        Type checkCall(CallExprAst *call, const Type &expectedType);
        Type checkNew(NewExprAst *newExpr, const Type &expectedType);
        Type checkObjectId(ObjectIdExprAst *objectId, const Type &expectedType);
        Type checkSelf(SelfExprAst *self, const Type &expectedType);
        Type checkIntegerLiteral(IntegerLiteralExprAst *literal, const Type &expectedType);
        Type checkStringLiteral(StringLiteralExprAst *literal, const Type &expectedType);
        Type checkBooleanLiteral(BooleanLiteralExprAst *literal, const Type &expectedType);
        Type checkUnitLiteral(UnitExprAst *literal, const Type &expectedType);

        // Utility methods
        bool isSubtype(const Type &subtype, const Type &supertype);
        std::string getCommonSupertype(const Type &type1, const Type &type2);
        bool checkMethodOverride(const std::string &methodName, const MethodSignature &newSig);
        void checkInheritanceCycles();
        bool hasCycle(const std::string &className, std::set<std::string> &visited,
                      std::set<std::string> &recursionStack);
        void checkMainClass();

        // String generation methods
        std::string getAnnotatedString(ExprAst *expr);
        std::string getAnnotatedString(ClassAst *classAst);
        std::string getAnnotatedString(FieldAst *fieldAst);
        std::string getAnnotatedString(MethodAst *methodAst);
        std::string getAnnotatedString(FormalAst *formalAst);
    };
}

#endif