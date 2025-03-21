#ifndef _AST_HPP
#define _AST_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

// Base node for all AST elements
class NodeBase {
protected:
    int lineNum, colNum;
public:
    NodeBase(int line, int col);
    virtual std::string serialize() const = 0;
    void reportError(const std::string &msg) const;
    void setFile(const std::string &file) const;
    virtual ~NodeBase();
};

// Base class for all expressions
class Expression : public NodeBase {
protected:
    std::string typeInfo;
public:
    Expression(int line, int col) : NodeBase(line, col) {}
    std::string getTypeInfo() const;
    virtual ~Expression() override;
};

// Compound expression (block)
class CompoundExpr : public Expression {
public:
    std::vector<Expression*> statements;
    CompoundExpr(int line, int col, std::vector<Expression*> stmts);
    std::string serialize() const override;
    ~CompoundExpr();
};

// Conditional expression
class ConditionalExpr : public Expression {
public:
    Expression *condition, *thenBranch, *elseBranch;
    ConditionalExpr(int line, int col, Expression *cond, Expression *thenExpr, Expression *elseExpr = nullptr);
    std::string serialize() const override;
    ~ConditionalExpr();
};

// Loop expression
class LoopExpr : public Expression {
public:
    Expression *condition, *body;
    LoopExpr(int line, int col, Expression *cond, Expression *loopBody);
    std::string serialize() const override;
    ~LoopExpr();
};

// Variable declaration
class VarDeclExpr : public Expression {
public:
    std::string name, varType;
    Expression *initializer, *scope;
    VarDeclExpr(int line, int col, std::string varName, std::string type, Expression *init, Expression *scopeExpr);
    std::string serialize() const override;
    ~VarDeclExpr();
};

// Binary operation
class BinaryOpExpr : public Expression {
public:
    std::string op;
    Expression *left, *right;
    BinaryOpExpr(int line, int col, std::string operation, Expression *lhs, Expression *rhs);
    std::string serialize() const override;
    ~BinaryOpExpr();
};

// Unary operation
class UnaryOpExpr : public Expression {
public:
    std::string op;
    Expression *operand;
    UnaryOpExpr(int line, int col, std::string operation, Expression *expr);
    std::string serialize() const override;
    ~UnaryOpExpr();
};

// Assignment expression
class AssignmentExpr : public Expression {
public:
    std::string target;
    Expression *value;
    AssignmentExpr(int line, int col, std::string targetName, Expression *val);
    std::string serialize() const override;
    ~AssignmentExpr();
};

// Method invocation
class MethodCallExpr : public Expression {
public:
    Expression *receiver;
    std::string methodName;
    std::vector<Expression*> arguments;
    MethodCallExpr(int line, int col, Expression *recv, std::string method, std::vector<Expression*> args);
    std::string serialize() const override;
    ~MethodCallExpr();
};

// Object instantiation
class NewObjectExpr : public Expression {
public:
    std::string className;
    NewObjectExpr(int line, int col, std::string type);
    std::string serialize() const override;
    ~NewObjectExpr();
};

// Literal value
class LiteralExpr : public Expression {
public:
    std::string value;
    LiteralExpr(int line, int col, std::string val, std::string type);
    std::string serialize() const override;
    ~LiteralExpr();
};

// Identifier reference
class IdentifierExpr : public Expression {
public:
    std::string name;
    IdentifierExpr(int line, int col, std::string id);
    std::string serialize() const override;
    ~IdentifierExpr();
};

// Method parameter
class Parameter : public NodeBase {
public:
    std::string name, type;
    Parameter(int line, int col, std::string paramName, std::string paramType);
    std::string serialize() const override;
    ~Parameter();
};

// Method definition
class MethodDef : public NodeBase {
public:
    std::string name, returnType;
    std::vector<Parameter*> params;
    CompoundExpr* body;
    MethodDef(int line, int col, std::string methodName, std::vector<Parameter*> parameters, 
             std::string retType, CompoundExpr* methodBody);
    std::string serialize() const override;
    ~MethodDef();
};

// Field definition
class FieldDef : public NodeBase {
public:
    std::string name, type;
    Expression* initialValue;
    FieldDef(int line, int col, std::string fieldName, std::string fieldType, Expression* init = nullptr);
    std::string serialize() const override;
    ~FieldDef();
};

// Class members container
struct ClassMembers {
    std::vector<FieldDef*> fields;
    std::vector<MethodDef*> methods;
};

// Class definition
class ClassDef : public NodeBase {
public:
    std::string name, parent;
    std::vector<FieldDef*> fields;
    std::vector<MethodDef*> methods;
    ClassDef(int line, int col, std::string className, std::string parentClass,
            std::vector<FieldDef*> classFields, std::vector<MethodDef*> classMethods);
    std::string serialize() const override;
    ~ClassDef();
};

// Program root
class Program : public NodeBase {
public:
    std::vector<ClassDef*> classes;
    Program(int line, int col, std::vector<ClassDef*> programClasses);
    std::string serialize() const override;
    ~Program();
};

#endif