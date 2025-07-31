/**
 * @brief Abstract Syntax Tree for VSOP compiler
 */

#ifndef _AST_HPP
#define _AST_HPP

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>

namespace VSOP
{
    // Forward declarations
    class ExprAst;
    class ClassAst;
    class FieldAst;
    class MethodAst;
    class FormalAst;

    class Ast 
    {
    public:
        virtual ~Ast() = default;
        virtual std::string getString() const = 0;
    };
    /**
     * @brief Program AST node representing the entire program
     */
    class ProgramAst : public Ast
    {
    public:
        /**
         * @brief Constructor for ProgramAst
         */
        ProgramAst() {}

        /**
         * @brief Destructor for ProgramAst
         */
        ~ProgramAst();

        /**
         * @brief Get string representation of the program
         * 
         * @return std::string String representation of the program
         */
        std::string getString() const;

        /**
         * @brief Vector of classes in the program
         */
        std::vector<ClassAst*> classes;
    };

    /**
     * @brief Class AST node representing a class definition
     */
    class ClassAst : public Ast
    {
    public:
        /**
         * @brief Constructor for ClassAst
         * 
         * @param name Name of the class
         * @param parent Parent class name (optional)
         */
        ClassAst(const std::string& name, const std::string& parent = "Object") 
            : name(name), parent(parent) {}

        /**
         * @brief Destructor for ClassAst
         */
        ~ClassAst();

        /**
         * @brief Get string representation of the class
         * 
         * @return std::string String representation of the class
         */
        std::string getString() const;

        /**
         * @brief Name of the class
         */
        std::string name;

        /**
         * @brief Parent class name
         */
        std::string parent;

        /**
         * @brief Fields of the class
         */
        std::vector<FieldAst*> fields;

        /**
         * @brief Methods of the class
         */
        std::vector<MethodAst*> methods;
    };

    /**
     * @brief Field AST node representing a class field
     */
    class FieldAst : public Ast
    {
    public:
        /**
         * @brief Constructor for FieldAst
         * 
         * @param name Field name
         * @param type Field type
         * @param initExpr Initialization expression (optional)
         */
        FieldAst(const std::string& name, const std::string& type, ExprAst* initExpr = nullptr)
            : name(name), type(type), initExpr(initExpr) {}

        /**
         * @brief Destructor for FieldAst
         */
        ~FieldAst();

        /**
         * @brief Get string representation of the field
         * 
         * @return std::string String representation of the field
         */
        std::string getString() const;

        /**
         * @brief Field name
         */
        std::string name;

        /**
         * @brief Field type
         */
        std::string type;

        /**
         * @brief Initialization expression (optional)
         */
        ExprAst* initExpr;
    };

    /**
     * @brief Formal parameter AST node
     */
    class FormalAst : public Ast
    {
    public:
        /**
         * @brief Constructor for FormalAst
         * 
         * @param name Parameter name
         * @param type Parameter type
         */
        FormalAst(const std::string& name, const std::string& type)
            : name(name), type(type) {}

        /**
         * @brief Get string representation of the formal parameter
         * 
         * @return std::string String representation of the formal parameter
         */
        std::string getString() const;

        /**
         * @brief Parameter name
         */
        std::string name;

        /**
         * @brief Parameter type
         */
        std::string type;
    };

    /**
     * @brief Method AST node representing a class method
     */
    class MethodAst : public Ast
    {
    public:
        /**
         * @brief Constructor for MethodAst
         * 
         * @param name Method name
         * @param returnType Return type
         * @param body Method body
         */
        MethodAst(const std::string& name, const std::string& returnType, ExprAst* body)
            : name(name), returnType(returnType), body(body) {}

        /**
         * @brief Destructor for MethodAst
         */
        ~MethodAst();

        /**
         * @brief Get string representation of the method
         * 
         * @return std::string String representation of the method
         */
        std::string getString() const;

        /**
         * @brief Method name
         */
        std::string name;

        /**
         * @brief Formal parameters
         */
        std::vector<FormalAst*> formals;

        /**
         * @brief Return type
         */
        std::string returnType;

        /**
         * @brief Method body
         */
        ExprAst* body;
    };

    /**
     * @brief Base class for all expressions
     */
    class ExprAst : public Ast
    {
    public:
        virtual ~ExprAst() = default;
        virtual std::string getString() const = 0;
    };

    /**
     * @brief Block expression
     */
    class BlockExprAst : public ExprAst
    {
    public:
        BlockExprAst() {}
        ~BlockExprAst() override;
        std::string getString() const override;
        std::vector<ExprAst*> expressions;
    };

    /**
     * @brief If expression
     */
    class IfExprAst : public ExprAst
    {
    public:
        IfExprAst(ExprAst* condition, ExprAst* thenExpr, ExprAst* elseExpr = nullptr)
            : condition(condition), thenExpr(thenExpr), elseExpr(elseExpr) {}
        ~IfExprAst() override;
        std::string getString() const override;
        ExprAst* condition;
        ExprAst* thenExpr;
        ExprAst* elseExpr;
    };

    /**
     * @brief While expression
     */
    class WhileExprAst : public ExprAst
    {
    public:
        WhileExprAst(ExprAst* condition, ExprAst* body)
            : condition(condition), body(body) {}
        ~WhileExprAst() override;
        std::string getString() const override;
        ExprAst* condition;
        ExprAst* body;
    };

    /**
     * @brief Let expression
     */
    class LetExprAst : public ExprAst
    {
    public:
        LetExprAst(const std::string& name, const std::string& type, 
                  ExprAst* initExpr, ExprAst* scopeExpr)
            : name(name), type(type), initExpr(initExpr), scopeExpr(scopeExpr) {}
        ~LetExprAst() override;
        std::string getString() const override;
        std::string name;
        std::string type;
        ExprAst* initExpr;
        ExprAst* scopeExpr;
    };

    /**
     * @brief Assignment expression
     */
    class AssignExprAst : public ExprAst
    {
    public:
        AssignExprAst(const std::string& name, ExprAst* expr)
            : name(name), expr(expr) {}
        ~AssignExprAst() override;
        std::string getString() const override;
        std::string name;
        ExprAst* expr;
    };

    /**
     * @brief Unary operation expression
     */
    class UnaryOpExprAst : public ExprAst
    {
    public:
        UnaryOpExprAst(const std::string& op, ExprAst* expr)
            : op(op), expr(expr) {}
        ~UnaryOpExprAst() override;
        std::string getString() const override;
        std::string op;
        ExprAst* expr;
    };

    /**
     * @brief Binary operation expression
     */
    class BinaryOpExprAst : public ExprAst
    {
    public:
        BinaryOpExprAst(const std::string& op, ExprAst* left, ExprAst* right)
            : op(op), left(left), right(right) {}
        ~BinaryOpExprAst() override;
        std::string getString() const override;
        std::string op;
        ExprAst* left;
        ExprAst* right;
    };

    /**
     * @brief Method call expression
     */
    class CallExprAst : public ExprAst
    {
    public:
        CallExprAst(ExprAst* object, const std::string& methodName)
            : object(object), methodName(methodName) {}
        ~CallExprAst() override;
        std::string getString() const override;
        ExprAst* object;
        std::string methodName;
        std::vector<ExprAst*> arguments;
    };

    /**
     * @brief New expression
     */
    class NewExprAst : public ExprAst
    {
    public:
        NewExprAst(const std::string& typeName)
            : typeName(typeName) {}
        ~NewExprAst() override;
        std::string getString() const override;
        std::string typeName;
    };

    /**
     * @brief Object identifier expression
     */
    class ObjectIdExprAst : public ExprAst
    {
    public:
        ObjectIdExprAst(const std::string& name)
            : name(name) {}
        ~ObjectIdExprAst() override;
        std::string getString() const override;
        std::string name;
    };

    /**
     * @brief Self expression
     */
    class SelfExprAst : public ExprAst
    {
    public:
        SelfExprAst() {}
        ~SelfExprAst() override;
        std::string getString() const override;
    };

    /**
     * @brief Integer literal expression
     */
    class IntegerLiteralExprAst : public ExprAst
    {
    public:
        IntegerLiteralExprAst(int value)
            : value(value) {}
        ~IntegerLiteralExprAst() override;
        std::string getString() const override;
        int value;
    };

    /**
     * @brief String literal expression
     */
    class StringLiteralExprAst : public ExprAst
    {
    public:
        StringLiteralExprAst(const std::string& value)
            : value(value) {}
        ~StringLiteralExprAst() override;
        std::string getString() const override;
        std::string value;
    };

    /**
     * @brief Boolean literal expression
     */
    class BooleanLiteralExprAst : public ExprAst
    {
    public:
        BooleanLiteralExprAst(bool value)
            : value(value) {}
        ~BooleanLiteralExprAst() override;
        std::string getString() const override;
        bool value;
    };

    /**
     * @brief Unit expression
     */
    class UnitExprAst : public ExprAst
    {
    public:
        UnitExprAst() {}
        ~UnitExprAst() override;
        std::string getString() const override;
    };
}

#endif