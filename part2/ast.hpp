#ifndef _AST_HPP
#define _AST_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

class BasicAst {
public:
    BasicAst(int line, int column);
    virtual std::string getString() const = 0;
    void printSemanticError(const std::string &message) const;
    void setSourceFile(const std::string &sourceFile) const;
    virtual ~BasicAst();
    int line, column;
};

class ExprAst : public BasicAst{
public:
    ExprAst(int line, int column) : BasicAst(line, column){}
    std::string getType() const;
    virtual ~ExprAst() override;
protected:
    std::string type;
};

class ExprBlockAst : public ExprAst{
public:
    ExprBlockAst(int line, int column, std::vector<ExprAst*> exprs);
    std::string getString() const override;
    ~ExprBlockAst();
    std::vector<ExprAst*> exprs;
};

class ExprIfAst : public ExprAst{
public:
    ExprIfAst(int line, int column, ExprAst *exprCond, ExprAst *exprThen);
    ExprIfAst(int line, int column, ExprAst *exprCond, ExprAst *exprThen, ExprAst *exprElse);
    std::string getString() const override;
    ~ExprIfAst();
    ExprAst *exprCond, *exprThen, *exprElse;
};

class ExprWhileAst : public ExprAst{
public:
    ExprWhileAst(int line, int column, ExprAst *exprCond, ExprAst *exprDo);
    std::string getString() const override;
    ~ExprWhileAst();
    ExprAst *exprCond, *exprDo;
};

class ExprLetAst : public ExprAst{
public:
    ExprLetAst(int line, int column, std::string object_id, std::string type_id, ExprAst *exprIn);
    ExprLetAst(int line, int column, std::string object_id, std::string type_id, ExprAst *assign, ExprAst *exprIn);
    std::string getString() const override;
    ~ExprLetAst();
    std::string object_id, type_id;
    ExprAst *assign, *exprIn;
};

class ExprBinopAst : public ExprAst{
public:
    ExprBinopAst(int ine, int column, std::string operator_str, ExprAst *expr1, ExprAst *expr2);
    std::string getString() const override;
    ~ExprBinopAst();
    std::string operator_str;
    ExprAst *expr1, *expr2;
};

class ExprUnopAst : public ExprAst{
public:
    ExprUnopAst(int line, int column, std::string operator_str, ExprAst *expr);
    std::string getString() const override;
    ~ExprUnopAst();
    std::string operator_str;
    ExprAst *expr;
};

class ExprAssignAst : public ExprAst{
public:
    ExprAssignAst(int line, int column, std::string object_id, ExprAst *assign);
    std::string getString() const override;
    ~ExprAssignAst();
    std::string object_id;
    ExprAst *assign;
};

class ExprCallAst : public ExprAst{
public:
    ExprCallAst(int line, int column, ExprAst *caller, std::string object_id, std::vector<ExprAst*> args);
    std::string getString() const override;
    ~ExprCallAst();
    ExprAst *caller;
    std::string object_id;
    std::vector<ExprAst*> args;
};

class ExprNewAst : public ExprAst{
public:
    ExprNewAst(int line, int column, std::string type_id);
    std::string getString() const override;
    ~ExprNewAst();
    std::string type_id;
};

class ExprLiteralAst : public ExprAst{
public:
    ExprLiteralAst(int line, int column, std::string id, std::string type);
    std::string getString() const override;
    ~ExprLiteralAst();
    std::string id, tmp_type;
};

class ExprObjectIdAst : public ExprAst{
public:
    ExprObjectIdAst(int line, int column, std::string id);
    std::string getString() const override;
    ~ExprObjectIdAst();
    std::string id;
};

class FormalAst : public BasicAst{
public:
    FormalAst(int line, int column, std::string parameterName, std::string parameterType);
    std::string getString() const override;
    ~FormalAst();
    std::string parameterName, parameterType;
};

class MethodAst : public BasicAst{
public:
    MethodAst(int line, int column, std::string name, std::vector<FormalAst*> formals, std::string type, ExprBlockAst* block);
    std::string getString() const override;
    ~MethodAst();
    std::string name, type;
    std::vector<FormalAst*> formals;
    ExprBlockAst* block;
};

class FieldAst : public BasicAst{
public:
    FieldAst(int line, int column, std::string variableName, std::string variableType);
    FieldAst(int line, int column, std::string variableName, std::string variableType, ExprAst* assign);
    std::string getString() const override;
    ~FieldAst();
    std::string variableName, variableType;
    ExprAst* assign;
};

struct ClassBody{
    std::vector<FieldAst*> fields;
    std::vector<MethodAst*> methods;
};

class ClassAst : public BasicAst{
public:
    ClassAst(int line, int column, std::string name, std::string parentName, std::vector<FieldAst*> fields, std::vector<MethodAst*> methods);
    std::string getString() const override;
    ~ClassAst();

    std::string name, parentName;
    std::vector<FieldAst*> fields;
    std::vector<MethodAst*> methods;
};

class ProgramAst : public BasicAst{
public:
    ProgramAst(int line, int column, std::vector<ClassAst*> classes);
    std::string getString() const override;
    ~ProgramAst();

    std::vector<ClassAst*> classes;
};

#endif