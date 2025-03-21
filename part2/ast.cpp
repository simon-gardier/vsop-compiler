/**
 * @brief Implementation of AST classes for VSOP compiler
 */

#include "ast.hpp"
#include <iterator>
#include <sstream>
#include <iomanip>

namespace VSOP
{
    /**
     * @brief Join strings with commas
     * 
     * @param strings Vector of strings to join
     * @return std::string Comma-separated string
     */
    static std::string enumerateElements(const std::vector<std::string>& strings)
    {
        std::string result;
        for(size_t i = 0; i < strings.size(); i++)
            result += strings[i] + (i == strings.size() - 1 ? "" : ", ");
        return result;
    }

    /**
     * @brief Format a list of strings with brackets and commas
     * 
     * @param strings Vector of strings to format
     * @return std::string Formatted string with brackets and commas
     */
    static std::string formatStringList(const std::vector<std::string>& strings)
    {
        return "[" + enumerateElements(strings) + "]";
    }

    // Main AST class destructors
    ProgramAst::~ProgramAst() {
        for (auto cls : classes) {
            delete cls;
        }
    }

    ClassAst::~ClassAst() {
        for (auto field : fields) {
            delete field;
        }
        for (auto method : methods) {
            delete method;
        }
    }

    FieldAst::~FieldAst() {
        if (initExpr) {
            delete initExpr;
        }
    }

    MethodAst::~MethodAst() {
        for (auto formal : formals) {
            delete formal;
        }
        if (body) {
            delete body;
        }
    }

    // Base class virtual destructor implementation is defaulted in the header

    // Derived class destructors
    BlockExprAst::~BlockExprAst() {
        for (auto expr : expressions) {
            delete expr;
        }
    }

    IfExprAst::~IfExprAst() {
        delete condition;
        delete thenExpr;
        if (elseExpr) {
            delete elseExpr;
        }
    }

    WhileExprAst::~WhileExprAst() {
        delete condition;
        delete body;
    }

    LetExprAst::~LetExprAst() {
        if (initExpr) {
            delete initExpr;
        }
        delete scopeExpr;
    }

    AssignExprAst::~AssignExprAst() {
        delete expr;
    }

    UnaryOpExprAst::~UnaryOpExprAst() {
        delete expr;
    }

    BinaryOpExprAst::~BinaryOpExprAst() {
        delete left;
        delete right;
    }

    CallExprAst::~CallExprAst() {
        delete object;
        for (auto arg : arguments) {
            delete arg;
        }
    }

    NewExprAst::~NewExprAst() {}
    ObjectIdExprAst::~ObjectIdExprAst() {}
    SelfExprAst::~SelfExprAst() {}
    IntegerLiteralExprAst::~IntegerLiteralExprAst() {}
    StringLiteralExprAst::~StringLiteralExprAst() {}
    BooleanLiteralExprAst::~BooleanLiteralExprAst() {}
    UnitExprAst::~UnitExprAst() {}

    std::string ProgramAst::getString() const
    {
        std::vector<std::string> classStrings;
        classStrings.reserve(classes.size());
        std::transform(classes.begin(), classes.end(), std::back_inserter(classStrings),
                    [](ClassAst* cls) { return cls->getString(); });
        return formatStringList(classStrings);
    }

    std::string ClassAst::getString() const
    {
        std::vector<std::string> fieldStrings;
        fieldStrings.reserve(fields.size());
        std::transform(fields.begin(), fields.end(), std::back_inserter(fieldStrings),
                    [](FieldAst* field) { return field->getString(); });
        
        std::vector<std::string> methodStrings;
        methodStrings.reserve(methods.size());
        std::transform(methods.begin(), methods.end(), std::back_inserter(methodStrings),
                    [](MethodAst* method) { return method->getString(); });
        
        return "Class(" + name + ", " + parent + ", " + 
               formatStringList(fieldStrings) + ", " + 
               formatStringList(methodStrings) + ")";
    }

    std::string FieldAst::getString() const
    {
        if (initExpr) {
            return "Field(" + name + ", " + type + ", " + initExpr->getString() + ")";
        } else {
            return "Field(" + name + ", " + type + ")";
        }
    }

    std::string FormalAst::getString() const
    {
        return name + " : " + type;
    }

    std::string MethodAst::getString() const
    {
        std::vector<std::string> formalStrings;
        formalStrings.reserve(formals.size());
        std::transform(formals.begin(), formals.end(), std::back_inserter(formalStrings),
                    [](FormalAst* formal) { return formal->getString(); });
        
        return "Method(" + name + ", " + formatStringList(formalStrings) + ", " + 
               returnType + ", " + body->getString() + ")";
    }

    std::string BlockExprAst::getString() const
    {
        std::vector<std::string> exprStrings;
        exprStrings.reserve(expressions.size());
        std::transform(expressions.begin(), expressions.end(), std::back_inserter(exprStrings),
                    [](ExprAst* expr) { return expr->getString(); });
        
        return formatStringList(exprStrings);
    }

    std::string IfExprAst::getString() const
    {
        if (elseExpr) {
            return "If(" + condition->getString() + ", " + 
                   thenExpr->getString() + ", " + 
                   elseExpr->getString() + ")";
        } else {
            return "If(" + condition->getString() + ", " + 
                   thenExpr->getString() + ")";
        }
    }

    std::string WhileExprAst::getString() const
    {
        return "While(" + condition->getString() + ", " + 
               body->getString() + ")";
    }

    std::string LetExprAst::getString() const
    {
        if (initExpr) {
            return "Let(" + name + ", " + type + ", " + 
                   initExpr->getString() + ", " + 
                   scopeExpr->getString() + ")";
        } else {
            return "Let(" + name + ", " + type + ", " + 
                   scopeExpr->getString() + ")";
        }
    }

    std::string AssignExprAst::getString() const
    {
        return "Assign(" + name + ", " + expr->getString() + ")";
    }

    std::string UnaryOpExprAst::getString() const
    {
        return "UnOp(" + op + ", " + expr->getString() + ")";
    }

    std::string BinaryOpExprAst::getString() const
    {
        return "BinOp(" + op + ", " + left->getString() + ", " + 
               right->getString() + ")";
    }

    std::string CallExprAst::getString() const
    {
        std::vector<std::string> argStrings;
        argStrings.reserve(arguments.size());
        std::transform(arguments.begin(), arguments.end(), std::back_inserter(argStrings),
                    [](ExprAst* arg) { return arg->getString(); });
        
        return "Call(" + object->getString() + ", " + methodName + ", " + 
               formatStringList(argStrings) + ")";
    }

    std::string NewExprAst::getString() const
    {
        return "New(" + typeName + ")";
    }

    std::string ObjectIdExprAst::getString() const
    {
        return name;
    }

    std::string SelfExprAst::getString() const
    {
        return "self";
    }

    std::string IntegerLiteralExprAst::getString() const
    {
        return std::to_string(value);
    }

    std::string StringLiteralExprAst::getString() const
    {
        return "\"" + value + "\"";
    }

    std::string BooleanLiteralExprAst::getString() const
    {
        return value ? "true" : "false";
    }

    std::string UnitExprAst::getString() const
    {
        return "()";
    }
}