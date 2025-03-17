/**
 * @brief AST (Abstract Syntax Tree) for VSOP compiler.
 */

#ifndef _AST_HPP
#define _AST_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include "parser.hpp"

namespace VSOP
{
    // Forward declarations
    class Type;
    class Expression;
    class Formal;
    class Method;
    class Field;
    class Class;
    class Program;

    /**
     * @brief Base class for all AST nodes
     */
    class ASTNode
    {
    public:
        ASTNode(const location& loc) : loc(loc) {}
        virtual ~ASTNode() = default;
        
        // Location in the source file
        location loc;
        
        // Virtual method for printing the node
        virtual void print(std::ostream& os) const = 0;
    };

    /**
     * @brief Type node
     */
    class Type : public ASTNode
    {
    public:
        Type(const location& loc, const std::string& name) 
            : ASTNode(loc), name(name) {}
        
        std::string name;
        
        void print(std::ostream& os) const override {
            os << name;
        }
    };

    /**
     * @brief Base class for all expressions
     */
    class Expression : public ASTNode
    {
    public:
        Expression(const location& loc) : ASTNode(loc) {}
    };

    /**
     * @brief Integer literal expression
     */
    class IntegerLiteral : public Expression
    {
    public:
        IntegerLiteral(const location& loc, int value) 
            : Expression(loc), value(value) {}
        
        int value;
        
        void print(std::ostream& os) const override {
            os << value;
        }
    };

    /**
     * @brief String literal expression
     */
    class StringLiteral : public Expression
    {
    public:
        StringLiteral(const location& loc, const std::string& value) 
            : Expression(loc), value(value) {}
        
        std::string value;
        
        void print(std::ostream& os) const override {
            os << "\"" << value << "\"";
        }
    };

    /**
     * @brief Boolean literal expression
     */
    class BooleanLiteral : public Expression
    {
    public:
        BooleanLiteral(const location& loc, bool value) 
            : Expression(loc), value(value) {}
        
        bool value;
        
        void print(std::ostream& os) const override {
            os << (value ? "true" : "false");
        }
    };

    /**
     * @brief Unit expression
     */
    class Unit : public Expression
    {
    public:
        Unit(const location& loc) : Expression(loc) {}
        
        void print(std::ostream& os) const override {
            os << "()";
        }
    };

    /**
     * @brief Object identifier expression
     */
    class ObjectIdentifier : public Expression
    {
    public:
        ObjectIdentifier(const location& loc, const std::string& name) 
            : Expression(loc), name(name) {}
        
        std::string name;
        
        void print(std::ostream& os) const override {
            os << name;
        }
    };

    /**
     * @brief Self expression
     */
    class Self : public Expression
    {
    public:
        Self(const location& loc) : Expression(loc) {}
        
        void print(std::ostream& os) const override {
            os << "self";
        }
    };

    /**
     * @brief Block expression
     */
    class Block : public Expression
    {
    public:
        Block(const location& loc, const std::vector<std::shared_ptr<Expression>>& expressions) 
            : Expression(loc), expressions(expressions) {}
        
        std::vector<std::shared_ptr<Expression>> expressions;
        
        void print(std::ostream& os) const override {
            os << "[";
            for (size_t i = 0; i < expressions.size(); ++i) {
                expressions[i]->print(os);
                if (i < expressions.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
        }
    };

    /**
     * @brief If expression
     */
    class If : public Expression
    {
    public:
        If(const location& loc, 
           std::shared_ptr<Expression> condition,
           std::shared_ptr<Expression> then_expr,
           std::shared_ptr<Expression> else_expr = nullptr) 
            : Expression(loc), 
              condition(condition), 
              then_expr(then_expr), 
              else_expr(else_expr) {}
        
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> then_expr;
        std::shared_ptr<Expression> else_expr;
        
        void print(std::ostream& os) const override {
            os << "If(";
            condition->print(os);
            os << ", ";
            then_expr->print(os);
            if (else_expr) {
                os << ", ";
                else_expr->print(os);
            }
            os << ")";
        }
    };

    /**
     * @brief While expression
     */
    class While : public Expression
    {
    public:
        While(const location& loc, 
              std::shared_ptr<Expression> condition,
              std::shared_ptr<Expression> body) 
            : Expression(loc), condition(condition), body(body) {}
        
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> body;
        
        void print(std::ostream& os) const override {
            os << "While(";
            condition->print(os);
            os << ", ";
            body->print(os);
            os << ")";
        }
    };

    /**
     * @brief Let expression
     */
    class Let : public Expression
    {
    public:
        Let(const location& loc, 
            const std::string& name,
            std::shared_ptr<Type> type,
            std::shared_ptr<Expression> init_expr,
            std::shared_ptr<Expression> scope_expr) 
            : Expression(loc), 
              name(name), 
              type(type), 
              init_expr(init_expr), 
              scope_expr(scope_expr) {}
        
        std::string name;
        std::shared_ptr<Type> type;
        std::shared_ptr<Expression> init_expr;
        std::shared_ptr<Expression> scope_expr;
        
        void print(std::ostream& os) const override {
            os << "Let(" << name << ", ";
            type->print(os);
            if (init_expr) {
                os << ", ";
                init_expr->print(os);
            }
            os << ", ";
            scope_expr->print(os);
            os << ")";
        }
    };

    /**
     * @brief Assign expression
     */
    class Assign : public Expression
    {
    public:
        Assign(const location& loc, 
               const std::string& name,
               std::shared_ptr<Expression> expr) 
            : Expression(loc), name(name), expr(expr) {}
        
        std::string name;
        std::shared_ptr<Expression> expr;
        
        void print(std::ostream& os) const override {
            os << "Assign(" << name << ", ";
            expr->print(os);
            os << ")";
        }
    };

    /**
     * @brief Unary operation expression
     */
    class UnaryOp : public Expression
    {
    public:
        UnaryOp(const location& loc, 
                const std::string& op,
                std::shared_ptr<Expression> expr) 
            : Expression(loc), op(op), expr(expr) {}
        
        std::string op;
        std::shared_ptr<Expression> expr;
        
        void print(std::ostream& os) const override {
            os << "UnOp(" << op << ", ";
            expr->print(os);
            os << ")";
        }
    };

    /**
     * @brief Binary operation expression
     */
    class BinaryOp : public Expression
    {
    public:
        BinaryOp(const location& loc, 
                 const std::string& op,
                 std::shared_ptr<Expression> left,
                 std::shared_ptr<Expression> right) 
            : Expression(loc), op(op), left(left), right(right) {}
        
        std::string op;
        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;
        
        void print(std::ostream& os) const override {
            os << "BinOp(" << op << ", ";
            left->print(os);
            os << ", ";
            right->print(os);
            os << ")";
        }
    };

    /**
     * @brief Call expression
     */
    class Call : public Expression
    {
    public:
        Call(const location& loc, 
             std::shared_ptr<Expression> object,
             const std::string& method,
             const std::vector<std::shared_ptr<Expression>>& args) 
            : Expression(loc), object(object), method(method), args(args) {}
        
        std::shared_ptr<Expression> object;
        std::string method;
        std::vector<std::shared_ptr<Expression>> args;
        
        void print(std::ostream& os) const override {
            os << "Call(";
            object->print(os);
            os << ", " << method << ", [";
            for (size_t i = 0; i < args.size(); ++i) {
                args[i]->print(os);
                if (i < args.size() - 1) {
                    os << ", ";
                }
            }
            os << "])";
        }
    };

    /**
     * @brief New expression
     */
    class New : public Expression
    {
    public:
        New(const location& loc, const std::string& type) 
            : Expression(loc), type(type) {}
        
        std::string type;
        
        void print(std::ostream& os) const override {
            os << "New(" << type << ")";
        }
    };

    /**
     * @brief Formal parameter
     */
    class Formal : public ASTNode
    {
    public:
        Formal(const location& loc, 
               const std::string& name,
               std::shared_ptr<Type> type) 
            : ASTNode(loc), name(name), type(type) {}
        
        std::string name;
        std::shared_ptr<Type> type;
        
        void print(std::ostream& os) const override {
            os << name << " : ";
            type->print(os);
        }
    };

    /**
     * @brief Method
     */
    class Method : public ASTNode
    {
    public:
        Method(const location& loc, 
               const std::string& name,
               const std::vector<std::shared_ptr<Formal>>& formals,
               std::shared_ptr<Type> return_type,
               std::shared_ptr<Block> body) 
            : ASTNode(loc), 
              name(name), 
              formals(formals), 
              return_type(return_type), 
              body(body) {}
        
        std::string name;
        std::vector<std::shared_ptr<Formal>> formals;
        std::shared_ptr<Type> return_type;
        std::shared_ptr<Block> body;
        
        void print(std::ostream& os) const override {
            os << "Method(" << name << ", [";
            for (size_t i = 0; i < formals.size(); ++i) {
                formals[i]->print(os);
                if (i < formals.size() - 1) {
                    os << ", ";
                }
            }
            os << "], ";
            return_type->print(os);
            os << ", ";
            body->print(os);
            os << ")";
        }
    };

    /**
     * @brief Field
     */
    class Field : public ASTNode
    {
    public:
        Field(const location& loc, 
              const std::string& name,
              std::shared_ptr<Type> type,
              std::shared_ptr<Expression> init_expr = nullptr) 
            : ASTNode(loc), 
              name(name), 
              type(type), 
              init_expr(init_expr) {}
        
        std::string name;
        std::shared_ptr<Type> type;
        std::shared_ptr<Expression> init_expr;
        
        void print(std::ostream& os) const override {
            os << "Field(" << name << ", ";
            type->print(os);
            if (init_expr) {
                os << ", ";
                init_expr->print(os);
            }
            os << ")";
        }
    };

    /**
     * @brief Class
     */
    class Class : public ASTNode
    {
    public:
        Class(const location& loc, 
              const std::string& name,
              const std::string& parent,
              const std::vector<std::shared_ptr<Field>>& fields,
              const std::vector<std::shared_ptr<Method>>& methods) 
            : ASTNode(loc), 
              name(name), 
              parent(parent), 
              fields(fields), 
              methods(methods) {}
        
        std::string name;
        std::string parent;
        std::vector<std::shared_ptr<Field>> fields;
        std::vector<std::shared_ptr<Method>> methods;
        
        void print(std::ostream& os) const override {
            os << "Class(" << name << ", " << parent << ", [";
            for (size_t i = 0; i < fields.size(); ++i) {
                fields[i]->print(os);
                if (i < fields.size() - 1) {
                    os << ", ";
                }
            }
            os << "], [";
            for (size_t i = 0; i < methods.size(); ++i) {
                methods[i]->print(os);
                if (i < methods.size() - 1) {
                    os << ", ";
                }
            }
            os << "])";
        }
    };

    /**
     * @brief Program
     */
    class Program : public ASTNode
    {
    public:
        Program(const std::vector<std::shared_ptr<Class>>& classes) 
            : ASTNode(location()), classes(classes) {}
        
        std::vector<std::shared_ptr<Class>> classes;
        
        void print(std::ostream& os) const override {
            os << "[";
            for (size_t i = 0; i < classes.size(); ++i) {
                classes[i]->print(os);
                if (i < classes.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
        }
    };
}

#endif // _AST_HPP