#include <unordered_set>
#include <string>

#include "ast.hpp"

std::string globalSourceFile;

static std::string enumerate_strings(const std::vector<std::string>& strings){
    std::string s;
    for(unsigned long i = 0 ; i < strings.size() ; i++)
        s += strings[i] + (i == strings.size()-1 ? "" : ", ");
    return s;
}

static std::string list_display(const std::vector<std::string>& strings){
    return "[" + enumerate_strings(strings) + "]";
}

static std::string function_display(const std::string name, const std::vector<std::string>& strings){
    return name + "(" + enumerate_strings(strings) + ")";
}

static bool is_primitive_type(std::string type){
    return !type.compare("int32") || !type.compare("unit") || !type.compare("bool") || !type.compare("string");
}

// ProgramAst
ProgramAst::ProgramAst(int line, int column, std::vector<ClassAst*> classes)
: BasicAst(line, column), classes(classes){}

std::string ProgramAst::getString() const{
    std::vector<std::string> classes_as_strings;
    classes_as_strings.reserve(classes.size());
    std::transform(classes.begin(), classes.end(), std::back_inserter(classes_as_strings),
                [](ClassAst* obj) { return obj->getString(); });
    return list_display(classes_as_strings);
}

ProgramAst::~ProgramAst(){
    for(auto c : classes)
        delete c;
    classes.clear();
}

// ClassAst
ClassAst::ClassAst(int line, int column, std::string name, std::string parentName, std::vector<FieldAst*> fields, std::vector<MethodAst*> methods) 
: BasicAst(line, column), name(name), parentName(parentName), fields(fields), methods(methods){}

std::string ClassAst::getString() const{
    std::vector<std::string> fields_as_string, methods_as_string;
    fields_as_string.reserve(fields.size());
    methods_as_string.reserve(methods.size());
    std::transform(fields.begin(), fields.end(), std::back_inserter(fields_as_string),
                [](FieldAst* obj) { return obj->getString(); });
    std::transform(methods.begin(), methods.end(), std::back_inserter(methods_as_string),
                [](MethodAst* obj) { return obj->getString(); });
    return function_display("Class", {name, parentName, list_display(fields_as_string), list_display(methods_as_string)});
}

ClassAst::~ClassAst(){
    for(auto f : fields)
        delete f;
    fields.clear();
    for(auto m : methods)
        delete m;
    methods.clear();
}

// FieldAst
FieldAst::FieldAst(int line, int column, std::string variableName, std::string variableType)
: BasicAst(line, column), variableName(variableName), variableType(variableType), assign(nullptr){}

FieldAst::FieldAst(int line, int column, std::string variableName, std::string variableType, ExprAst* assign)
: BasicAst(line, column), variableName(variableName), variableType(variableType), assign(assign){}

std::string FieldAst::getString() const{
    return function_display("Field", {variableName, variableType, assign ? assign->getString() : "<no-init>"});
}

FieldAst::~FieldAst(){
    if(assign)
        delete assign;
}

// MethodAst
MethodAst::MethodAst(int line, int column, std::string name, std::vector<FormalAst*> formals, std::string type, ExprBlockAst* block)
: BasicAst(line, column), name(name), type(type), formals(formals), block(block){}

std::string MethodAst::getString() const{
    std::vector<std::string> formals_as_string;
    formals_as_string.reserve(formals.size());
    std::transform(formals.begin(), formals.end(), std::back_inserter(formals_as_string),
                [](FormalAst* obj) { return obj->getString(); });
    return function_display("Method", {name, list_display(formals_as_string), type, block->getString()});
}

MethodAst::~MethodAst(){
    for(auto f : formals)
        delete f;
    formals.clear();
    delete block;
}

// FormalAst
FormalAst::FormalAst(int line, int column, std::string parameterName, std::string parameterType)
: BasicAst(line, column), parameterName(parameterName), parameterType(parameterType){}

std::string FormalAst::getString() const{
    return function_display("Formal", {parameterName, parameterType});
}

FormalAst::~FormalAst(){}

// ExprAst
std::string ExprAst::getType() const{
    return type;
}

ExprAst::~ExprAst(){}

// ExprBlockAst
ExprBlockAst::ExprBlockAst(int line, int column, std::vector<ExprAst*> exprs)
: ExprAst(line, column), exprs(exprs){
    type = "unit";
}

std::string ExprBlockAst::getString() const{
    std::vector<std::string> exprs_as_string;
    exprs_as_string.reserve(exprs.size());
    std::transform(exprs.begin(), exprs.end(), std::back_inserter(exprs_as_string),
                [](ExprAst* obj) { return obj->getString(); });
    return function_display("Block", {list_display(exprs_as_string)});
}

ExprBlockAst::~ExprBlockAst(){
    for(auto e : exprs)
        delete e;
    exprs.clear();
}

// ExprIfAst
ExprIfAst::ExprIfAst(int line, int column, ExprAst *exprCond, ExprAst *exprThen)
: ExprAst(line, column), exprCond(exprCond), exprThen(exprThen), exprElse(nullptr){
    type = "unit";
}

ExprIfAst::ExprIfAst(int line, int column, ExprAst *exprCond, ExprAst *exprThen, ExprAst *exprElse)
: ExprAst(line, column), exprCond(exprCond), exprThen(exprThen), exprElse(exprElse){}

std::string ExprIfAst::getString() const{
    return function_display("If", {exprCond->getString(), exprThen->getString(), exprElse ? exprElse->getString() : "<no-else>"});
}

ExprIfAst::~ExprIfAst(){
    delete exprCond;
    delete exprThen;
    if(exprElse)
        delete exprElse;
}

// ExprWhileAst
ExprWhileAst::ExprWhileAst(int line, int column, ExprAst *exprCond, ExprAst *exprDo)
: ExprAst(line, column), exprCond(exprCond), exprDo(exprDo){
    type = "unit";
}

std::string ExprWhileAst::getString() const{
    return function_display("While", {exprCond->getString(), exprDo->getString()});
}

ExprWhileAst::~ExprWhileAst(){
    delete exprCond;
    delete exprDo;
}

// ExprLetAst
ExprLetAst::ExprLetAst(int line, int column, std::string object_id, std::string type_id, ExprAst *exprIn)
: ExprAst(line, column), object_id(object_id), type_id(type_id), assign(nullptr), exprIn(exprIn){}

ExprLetAst::ExprLetAst(int line, int column, std::string object_id, std::string type_id, ExprAst *assign, ExprAst *exprIn)
: ExprAst(line, column), object_id(object_id), type_id(type_id), assign(assign), exprIn(exprIn){}

std::string ExprLetAst::getString() const{
    return function_display("Let", {object_id, type_id, assign ? assign->getString() : "<no-init>", exprIn->getString()});
}

ExprLetAst::~ExprLetAst(){
    if(assign)
        delete assign;
    delete exprIn;
}

// ExprBinopAst
ExprBinopAst::ExprBinopAst(int line, int column, std::string operator_str, ExprAst *expr1, ExprAst *expr2)
: ExprAst(line, column), operator_str(operator_str), expr1(expr1), expr2(expr2){}

std::string ExprBinopAst::getString() const{
    return function_display("BinOp", {operator_str, expr1->getString(), expr2->getString()});
}

ExprBinopAst::~ExprBinopAst(){
    delete expr1;
    delete expr2;
}

// ExprUnopAst
ExprUnopAst::ExprUnopAst(int line, int column, std::string operator_str, ExprAst *expr)
: ExprAst(line, column), operator_str(operator_str), expr(expr){}

std::string ExprUnopAst::getString() const{
    return function_display("UnOp", {operator_str, expr->getString()});
}

ExprUnopAst::~ExprUnopAst(){
    delete expr;
}

// ExprAssignAst
ExprAssignAst::ExprAssignAst(int line, int column, std::string object_id, ExprAst *assign)
: ExprAst(line, column), object_id(object_id), assign(assign){}

std::string ExprAssignAst::getString() const{
    return function_display("Assign", {object_id, assign->getString()});
}

ExprAssignAst::~ExprAssignAst(){
    delete assign;
}

// ExprCallAst
ExprCallAst::ExprCallAst(int line, int column, ExprAst *caller, std::string object_id, std::vector<ExprAst*> args)
: ExprAst(line, column), caller(caller), object_id(object_id), args(args){}

std::string ExprCallAst::getString() const{
    std::vector<std::string> args_as_string;
    args_as_string.reserve(args.size());
    std::transform(args.begin(), args.end(), std::back_inserter(args_as_string),
                [](ExprAst* obj) { return obj->getString(); });
    return function_display("Call", {caller->getString(), object_id, list_display(args_as_string)});
}

ExprCallAst::~ExprCallAst(){
    delete caller;
    for(auto a : args)
        delete a;
    args.clear();
}

// ExprNewAst
ExprNewAst::ExprNewAst(int line, int column, std::string type_id)
: ExprAst(line, column), type_id(type_id){
    type = type_id;
}

std::string ExprNewAst::getString() const{
    return function_display("New", {type_id});
}

ExprNewAst::~ExprNewAst(){}

// ExprLiteralAst
ExprLiteralAst::ExprLiteralAst(int line, int column, std::string id, std::string type)
: ExprAst(line, column), id(id), tmp_type(type){
    this->type = type;
}

std::string ExprLiteralAst::getString() const{
    return function_display("Literal", {id, type});
}

ExprLiteralAst::~ExprLiteralAst(){}

// ExprObjectIdAst
ExprObjectIdAst::ExprObjectIdAst(int line, int column, std::string id)
: ExprAst(line, column), id(id){}

std::string ExprObjectIdAst::getString() const{
    return function_display("ObjectIdentifier", {id});
}

ExprObjectIdAst::~ExprObjectIdAst(){}

// BasicAst
BasicAst::BasicAst(int line, int column)
: line(line), column(column){}

void BasicAst::printSemanticError(const std::string &message) const{
    std::cerr << globalSourceFile << ":" << line << ":" << column << ": semantic error: " << message << std::endl;
}

void BasicAst::setSourceFile(const std::string &sourceFile) const{
    globalSourceFile = sourceFile;
}

BasicAst::~BasicAst(){}