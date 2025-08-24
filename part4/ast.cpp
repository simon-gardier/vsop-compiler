/**
 * @brief Implementation of AST classes for VSOP compiler
 */

#include "ast.hpp"
#include <iostream>
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
    static std::string enumerateElements(const std::vector<std::string> &strings)
    {
        std::string result;
        for (size_t i = 0; i < strings.size(); i++)
            result += strings[i] + (i == strings.size() - 1 ? "" : ", ");
        return result;
    }

    /**
     * @brief Format a list of strings with brackets and commas
     *
     * @param strings Vector of strings to format
     * @return std::string Formatted string with brackets and commas
     */
    static std::string formatStringList(const std::vector<std::string> &strings)
    {
        return "[" + enumerateElements(strings) + "]";
    }

    // Main AST class destructors
    ProgramAst::~ProgramAst()
    {
        for (auto cls : classes)
        {
            delete cls;
        }
    }

    ClassAst::~ClassAst()
    {
        for (auto field : fields)
        {
            delete field;
        }
        for (auto method : methods)
        {
            delete method;
        }
    }

    FieldAst::~FieldAst()
    {
        if (initExpr)
        {
            delete initExpr;
        }
    }

    MethodAst::~MethodAst()
    {
        for (auto formal : formals)
        {
            delete formal;
        }
        if (body)
        {
            delete body;
        }
    }

    // Base class virtual destructor implementation is defaulted in the header

    // Derived class destructors
    BlockExprAst::~BlockExprAst()
    {
        for (auto expr : expressions)
        {
            delete expr;
        }
    }

    IfExprAst::~IfExprAst()
    {
        delete condition;
        delete thenExpr;
        if (elseExpr)
        {
            delete elseExpr;
        }
    }

    WhileExprAst::~WhileExprAst()
    {
        delete condition;
        delete body;
    }

    LetExprAst::~LetExprAst()
    {
        if (initExpr)
        {
            delete initExpr;
        }
        delete scopeExpr;
    }

    AssignExprAst::~AssignExprAst()
    {
        delete expr;
    }

    UnaryOpExprAst::~UnaryOpExprAst()
    {
        delete expr;
    }

    BinaryOpExprAst::~BinaryOpExprAst()
    {
        delete left;
        delete right;
    }

    CallExprAst::~CallExprAst()
    {
        delete object;
        for (auto arg : arguments)
        {
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
                       [](ClassAst *cls)
                       { return cls->getString(); });
        return formatStringList(classStrings);
    }

    std::string ClassAst::getString() const
    {
        std::vector<std::string> fieldStrings;
        fieldStrings.reserve(fields.size());
        std::transform(fields.begin(), fields.end(), std::back_inserter(fieldStrings),
                       [](FieldAst *field)
                       { return field->getString(); });

        std::vector<std::string> methodStrings;
        methodStrings.reserve(methods.size());
        std::transform(methods.begin(), methods.end(), std::back_inserter(methodStrings),
                       [](MethodAst *method)
                       { return method->getString(); });

        return "Class(" + name + ", " + parent + ", " +
               formatStringList(fieldStrings) + ", " +
               formatStringList(methodStrings) + ")";
    }

    std::string FieldAst::getString() const
    {
        if (initExpr)
        {
            return "Field(" + name + ", " + type + ", " + initExpr->getString() + ")";
        }
        else
        {
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
                       [](FormalAst *formal)
                       { return formal->getString(); });

        return "Method(" + name + ", " + formatStringList(formalStrings) + ", " +
               returnType + ", " + body->getString() + ")";
    }

    std::string BlockExprAst::getString() const
    {
        std::vector<std::string> exprStrings;
        exprStrings.reserve(expressions.size());
        std::transform(expressions.begin(), expressions.end(), std::back_inserter(exprStrings),
                       [](ExprAst *expr)
                       { return expr->getString(); });

        std::string result = formatStringList(exprStrings);
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string IfExprAst::getString() const
    {
        std::string conditionStr = condition->getString();
        std::string thenStr = thenExpr->getString();

        std::string result;
        if (elseExpr)
        {
            std::string elseStr = elseExpr->getString();
            result = "If(" + conditionStr + ", " + thenStr + ", " + elseStr + ")";
        }
        else
        {
            result = "If(" + conditionStr + ", " + thenStr + ")";
        }

        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string WhileExprAst::getString() const
    {
        std::string conditionStr = condition->getString();
        std::string bodyStr = body->getString();

        std::string result = "While(" + conditionStr + ", " + bodyStr + ")";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string LetExprAst::getString() const
    {
        std::string result;
        if (initExpr)
        {
            std::string initStr = initExpr->getString();
            std::string scopeStr = scopeExpr->getString();
            result = "Let(" + name + ", " + type + ", " + initStr + ", " + scopeStr + ")";
        }
        else
        {
            std::string scopeStr = scopeExpr->getString();
            result = "Let(" + name + ", " + type + ", " + scopeStr + ")";
        }

        if (hasTypeInfo())
        {
            result += " : " + ExprAst::type;
        }
        return result;
    }

    std::string AssignExprAst::getString() const
    {
        std::string exprStr = expr->getString();
        std::string result = "Assign(" + name + ", " + exprStr + ")";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string UnaryOpExprAst::getString() const
    {
        std::string exprStr = expr->getString();
        std::string result = "UnOp(" + op + ", " + exprStr + ")";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string BinaryOpExprAst::getString() const
    {
        std::string leftStr = left->getString();
        std::string rightStr = right->getString();

        std::string result = "BinOp(" + op + ", " + leftStr + ", " + rightStr + ")";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string CallExprAst::getString() const
    {
        std::string objectStr = object->getString();

        std::vector<std::string> argStrings;
        argStrings.reserve(arguments.size());
        std::transform(arguments.begin(), arguments.end(), std::back_inserter(argStrings),
                       [](ExprAst *arg)
                       { return arg->getString(); });

        std::string result = "Call(" + objectStr + ", " + methodName + ", " +
                             formatStringList(argStrings) + ")";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string NewExprAst::getString() const
    {
        std::string result = "New(" + typeName + ")";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string ObjectIdExprAst::getString() const
    {
        std::string result = name;
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string SelfExprAst::getString() const
    {
        std::string result = "self";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string IntegerLiteralExprAst::getString() const
    {
        std::string result = std::to_string(value);
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string StringLiteralExprAst::getString() const
    {
        std::string result = "\"" + value + "\"";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string BooleanLiteralExprAst::getString() const
    {
        std::string result = value ? "true" : "false";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }

    std::string UnitExprAst::getString() const
    {
        std::string result = "()";
        if (hasTypeInfo())
        {
            result += " : " + type;
        }
        return result;
    }
}