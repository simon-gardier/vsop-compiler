#include <unordered_set>
#include <string>

#include "ast.hpp"

static std::string currentSourceFile;

static std::string joinStrings(const std::vector<std::string>& items, const std::string& delimiter = ", ") {
    std::string result;
    for(size_t i = 0; i < items.size(); i++) {
        result += items[i];
        if(i < items.size() - 1) result += delimiter;
    }
    return result;
}

static std::string formatList(const std::vector<std::string>& items) {
    return "[" + joinStrings(items) + "]";
}

static std::string formatCall(const std::string& name, const std::vector<std::string>& args) {
    return name + "(" + joinStrings(args) + ")";
}

// NodeBase implementation
NodeBase::NodeBase(int line, int col) : lineNum(line), colNum(col) {}

void NodeBase::reportError(const std::string& msg) const {
    std::cerr << currentSourceFile << ":" << lineNum << ":" << colNum << ": semantic error: " << msg << std::endl;
}

void NodeBase::setFile(const std::string& file) const {
    currentSourceFile = file;
}

NodeBase::~NodeBase() {}

// Expression implementation
std::string Expression::getTypeInfo() const {
    return typeInfo;
}

Expression::~Expression() {}

// CompoundExpr implementation
CompoundExpr::CompoundExpr(int line, int col, std::vector<Expression*> stmts)
: Expression(line, col), statements(stmts) {
    typeInfo = "unit";
}

std::string CompoundExpr::serialize() const {
    std::vector<std::string> stmtStrings;
    stmtStrings.reserve(statements.size());
    for(auto stmt : statements) {
        stmtStrings.push_back(stmt->serialize());
    }
    return formatCall("Block", {formatList(stmtStrings)});
}

CompoundExpr::~CompoundExpr() {
    for(auto stmt : statements) delete stmt;
}

// ConditionalExpr implementation
ConditionalExpr::ConditionalExpr(int line, int col, Expression* cond, Expression* thenExpr, Expression* elseExpr)
: Expression(line, col), condition(cond), thenBranch(thenExpr), elseBranch(elseExpr) {}

std::string ConditionalExpr::serialize() const {
    return formatCall("If", {
        condition->serialize(),
        thenBranch->serialize(),
        elseBranch ? elseBranch->serialize() : "<no-else>"
    });
}

ConditionalExpr::~ConditionalExpr() {
    delete condition;
    delete thenBranch;
    if(elseBranch) delete elseBranch;
}

// LoopExpr implementation
LoopExpr::LoopExpr(int line, int col, Expression* cond, Expression* loopBody)
: Expression(line, col), condition(cond), body(loopBody) {
    typeInfo = "unit";
}

std::string LoopExpr::serialize() const {
    return formatCall("While", {condition->serialize(), body->serialize()});
}

LoopExpr::~LoopExpr() {
    delete condition;
    delete body;
}

// VarDeclExpr implementation
VarDeclExpr::VarDeclExpr(int line, int col, std::string varName, std::string type, 
                         Expression* init, Expression* scopeExpr)
: Expression(line, col), name(varName), varType(type), initializer(init), scope(scopeExpr) {}

std::string VarDeclExpr::serialize() const {
    return formatCall("Let", {
        name,
        varType,
        initializer ? initializer->serialize() : "<no-init>",
        scope->serialize()
    });
}

VarDeclExpr::~VarDeclExpr() {
    if(initializer) delete initializer;
    delete scope;
}

// BinaryOpExpr implementation
BinaryOpExpr::BinaryOpExpr(int line, int col, std::string operation, Expression* lhs, Expression* rhs)
: Expression(line, col), op(operation), left(lhs), right(rhs) {}

std::string BinaryOpExpr::serialize() const {
    return formatCall("BinOp", {op, left->serialize(), right->serialize()});
}

BinaryOpExpr::~BinaryOpExpr() {
    delete left;
    delete right;
}

// UnaryOpExpr implementation
UnaryOpExpr::UnaryOpExpr(int line, int col, std::string operation, Expression* expr)
: Expression(line, col), op(operation), operand(expr) {}

std::string UnaryOpExpr::serialize() const {
    return formatCall("UnOp", {op, operand->serialize()});
}

UnaryOpExpr::~UnaryOpExpr() {
    delete operand;
}

// AssignmentExpr implementation
AssignmentExpr::AssignmentExpr(int line, int col, std::string targetName, Expression* val)
: Expression(line, col), target(targetName), value(val) {}

std::string AssignmentExpr::serialize() const {
    return formatCall("Assign", {target, value->serialize()});
}

AssignmentExpr::~AssignmentExpr() {
    delete value;
}

// MethodCallExpr implementation
MethodCallExpr::MethodCallExpr(int line, int col, Expression* recv, std::string method, std::vector<Expression*> args)
: Expression(line, col), receiver(recv), methodName(method), arguments(args) {}

std::string MethodCallExpr::serialize() const {
    std::vector<std::string> argStrings;
    argStrings.reserve(arguments.size());
    for(auto arg : arguments) {
        argStrings.push_back(arg->serialize());
    }
    return formatCall("Call", {receiver->serialize(), methodName, formatList(argStrings)});
}

MethodCallExpr::~MethodCallExpr() {
    delete receiver;
    for(auto arg : arguments) delete arg;
}

// NewObjectExpr implementation
NewObjectExpr::NewObjectExpr(int line, int col, std::string type)
: Expression(line, col), className(type) {
    typeInfo = type;
}

std::string NewObjectExpr::serialize() const {
    return formatCall("New", {className});
}

NewObjectExpr::~NewObjectExpr() {}

// LiteralExpr implementation
LiteralExpr::LiteralExpr(int line, int col, std::string val, std::string type)
: Expression(line, col), value(val) {
    typeInfo = type;
}

std::string LiteralExpr::serialize() const {
    return formatCall("Literal", {value, typeInfo});
}

LiteralExpr::~LiteralExpr() {}

// IdentifierExpr implementation
IdentifierExpr::IdentifierExpr(int line, int col, std::string id)
: Expression(line, col), name(id) {}

std::string IdentifierExpr::serialize() const {
    return formatCall("ObjectIdentifier", {name});
}

IdentifierExpr::~IdentifierExpr() {}

// Parameter implementation
Parameter::Parameter(int line, int col, std::string paramName, std::string paramType)
: NodeBase(line, col), name(paramName), type(paramType) {}

std::string Parameter::serialize() const {
    return formatCall("Formal", {name, type});
}

Parameter::~Parameter() {}

// MethodDef implementation
MethodDef::MethodDef(int line, int col, std::string methodName, std::vector<Parameter*> parameters,
                     std::string retType, CompoundExpr* methodBody)
: NodeBase(line, col), name(methodName), returnType(retType), params(parameters), body(methodBody) {}

std::string MethodDef::serialize() const {
    std::vector<std::string> paramStrings;
    paramStrings.reserve(params.size());
    for(auto param : params) {
        paramStrings.push_back(param->serialize());
    }
    return formatCall("Method", {name, formatList(paramStrings), returnType, body->serialize()});
}

MethodDef::~MethodDef() {
    for(auto param : params) delete param;
    delete body;
}

// FieldDef implementation
FieldDef::FieldDef(int line, int col, std::string fieldName, std::string fieldType, Expression* init)
: NodeBase(line, col), name(fieldName), type(fieldType), initialValue(init) {}

std::string FieldDef::serialize() const {
    return formatCall("Field", {name, type, initialValue ? initialValue->serialize() : "<no-init>"});
}

FieldDef::~FieldDef() {
    if(initialValue) delete initialValue;
}

// ClassDef implementation
ClassDef::ClassDef(int line, int col, std::string className, std::string parentClass,
                   std::vector<FieldDef*> classFields, std::vector<MethodDef*> classMethods)
: NodeBase(line, col), name(className), parent(parentClass), fields(classFields), methods(classMethods) {}

std::string ClassDef::serialize() const {
    std::vector<std::string> fieldStrings, methodStrings;
    fieldStrings.reserve(fields.size());
    methodStrings.reserve(methods.size());
    
    for(auto field : fields) fieldStrings.push_back(field->serialize());
    for(auto method : methods) methodStrings.push_back(method->serialize());
    
    return formatCall("Class", {name, parent, formatList(fieldStrings), formatList(methodStrings)});
}

ClassDef::~ClassDef() {
    for(auto field : fields) delete field;
    for(auto method : methods) delete method;
}

// Program implementation
Program::Program(int line, int col, std::vector<ClassDef*> programClasses)
: NodeBase(line, col), classes(programClasses) {}

std::string Program::serialize() const {
    std::vector<std::string> classStrings;
    classStrings.reserve(classes.size());
    for(auto cls : classes) {
        classStrings.push_back(cls->serialize());
    }
    return formatList(classStrings);
}

Program::~Program() {
    for(auto cls : classes) delete cls;
}