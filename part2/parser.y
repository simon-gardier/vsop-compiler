/**
 * @brief Parser for VSOP compiler. Based on course example
 */

%skeleton "lalr1.cc" // -*- C++ -*-
%language "c++"
%require "3.7.5"
%locations

%defines

// Put parser inside a namespace
%define api.namespace {VSOP}

// Give the name of the parser class
%define api.parser.class {Parser}

// Force the token kind enum (used by the lexer) and the symbol kind enum
// (used by the parser) to use the same value for the tokens.
// (e.g. '+' will be represented by the same integer value in both enums.)
%define api.token.raw

// Tokens contain their type, value and location
// Also allow to use the make_TOKEN functions
%define api.token.constructor

// Allow to use C++ objects as semantic values
%define api.value.type variant

// Add some assertions.
%define parse.assert

// Debugging
%define parse.trace
%define parse.error verbose
%debug

// C++ code put inside header file
%code requires {
    #include <string>
    #include <vector>
    #include <memory>
    #include "ast.hpp"

    namespace VSOP
    {
        class Driver;
    }
}

// Add an argument to the parser constructor
%parse-param {VSOP::Driver &driver}

%code {
    #include "driver.hpp"
}

// VSOP tokens definition
%token <int>         INTEGER_LITERAL
%token <std::string> STRING_LITERAL
%token <std::string> TYPE_IDENTIFIER
%token <std::string> OBJECT_IDENTIFIER
// Operators
%token LBRACE "{"
%token RBRACE "}"
%token LPAR "("
%token RPAR ")"
%token COLON ":"
%token SEMICOLON ";"
%token COMMA ","
%token PLUS "+"
%token MINUS "-"
%token TIMES "*"
%token DIV "/"
%token POW "^"
%token DOT "."
%token EQUAL "="
%token LOWER "<"
%token LOWER_EQUAL "<="
%token ASSIGN "<-"
// Keywords
%token AND "and"
%token BOOL "bool"
%token CLASS "class"
%token DO "do"
%token ELSE "else"
%token EXTENDS "extends"
%token FALSE "false"
%token IF "if"
%token IN "in"
%token INT32 "int32"
%token ISNULL "isnull"
%token LET "let"
%token NEW "new"
%token NOT "not"
%token SELF "self"
%token STRING "string"
%token THEN "then"
%token TRUE "true"
%token UNIT "unit"
%token WHILE "while"

// Define the types for non-terminals
%type <VSOP::ProgramAst*> program
%type <VSOP::ClassAst*> class
%type <std::vector<VSOP::ClassAst*>> class_list
%type <VSOP::FieldAst*> field
%type <VSOP::MethodAst*> method
%type <std::vector<VSOP::Ast*>> member_list
%type <VSOP::Ast*> member
%type <VSOP::FormalAst*> formal
%type <std::vector<VSOP::FormalAst*>> formal_list formals
%type <VSOP::ExprAst*> expr block
%type <std::vector<VSOP::ExprAst*>> expr_list args
%type <std::string> type

// Define operator precedence and associativity
%right ASSIGN
%left AND
%right UNOT
%nonassoc EQUAL LOWER LOWER_EQUAL
%left PLUS MINUS
%left TIMES DIV
%right UMINUS UISNULL
%right POW
%left DOT

%%
// Grammar rules for VSOP language

// Program is a list of classes
program
    : class_list
        {
            $$ = new ProgramAst();
            $$->classes = $1;
            driver.programAst.reset($$);
        }
    ;

class_list
    : class
        {
            $$ = std::vector<ClassAst*>();
            $$.push_back($1);
        }
    | class_list class
        {
            $$ = $1;
            $$.push_back($2);
        }
    ;

// Class definition
class
    : "class" TYPE_IDENTIFIER "{" member_list "}"
        {
            VSOP::ClassAst* cls = new VSOP::ClassAst($2);
            // Separate members into fields and methods.
            for (auto mem : $4) {
                if (auto f = dynamic_cast<VSOP::FieldAst*>(mem))
                    cls->fields.push_back(f);
                else if (auto m = dynamic_cast<VSOP::MethodAst*>(mem))
                    cls->methods.push_back(m);
            }
            $$ = cls;
        }
    | "class" TYPE_IDENTIFIER "extends" TYPE_IDENTIFIER "{" member_list "}"
        {
            VSOP::ClassAst* cls = new VSOP::ClassAst($2, $4);
            for (auto mem : $6) {
                if (auto f = dynamic_cast<VSOP::FieldAst*>(mem))
                    cls->fields.push_back(f);
                else if (auto m = dynamic_cast<VSOP::MethodAst*>(mem))
                    cls->methods.push_back(m);
            }
            $$ = cls;
        }
    ;

member_list
    : /* empty */
        { $$ = std::vector<VSOP::Ast*>(); }
    | member_list member
        { $$ = $1; $$.push_back($2); }
    ;

member
    : field  { $$ = $1; }
    | method { $$ = $1; }
    ;

// Field definition
field
    : OBJECT_IDENTIFIER ":" type ";"
        {
            $$ = new FieldAst($1, $3);
        }
    | OBJECT_IDENTIFIER ":" type "<-" expr ";"
        {
            $$ = new FieldAst($1, $3, $5);
        }
    ;

// Method definition
method
    : OBJECT_IDENTIFIER "(" formals ")" ":" type block
        {
            $$ = new MethodAst($1, $6, $7);
            $$->formals = $3;
        }
    ;

// Formal parameters
formals
    : /* empty */
        {
            $$ = std::vector<FormalAst*>();
        }
    | formal_list
        {
            $$ = $1;
        }
    ;

formal_list
    : formal
        {
            $$ = std::vector<FormalAst*>();
            $$.push_back($1);
        }
    | formal_list "," formal
        {
            $$ = $1;
            $$.push_back($3);
        }
    ;

formal
    : OBJECT_IDENTIFIER ":" type
        {
            $$ = new FormalAst($1, $3);
        }
    ;

// Types
type
    : TYPE_IDENTIFIER
        {
            $$ = $1;
        }
    | "int32"
        {
            $$ = "int32";
        }
    | "bool"
        {
            $$ = "bool";
        }
    | "string"
        {
            $$ = "string";
        }
    | "unit"
        {
            $$ = "unit";
        }
    ;

// Block of expressions
block
    : "{" expr_list "}"
        {
            BlockExprAst* block = new BlockExprAst();
            block->expressions = $2;
            $$ = block;
        }
    ;

expr_list
    : expr
        {
            $$ = std::vector<ExprAst*>();
            $$.push_back($1);
        }
    | expr_list ";" expr
        {
            $$ = $1;
            $$.push_back($3);
        }
    ;

// Expressions
expr
    : "if" expr "then" expr
        {
            $$ = new IfExprAst($2, $4);
        }
    | "if" expr "then" expr "else" expr
        {
            $$ = new IfExprAst($2, $4, $6);
        }
    | "while" expr "do" expr
        {
            $$ = new WhileExprAst($2, $4);
        }
    | "let" OBJECT_IDENTIFIER ":" type "in" expr
        {
            $$ = new LetExprAst($2, $4, nullptr, $6);
        }
    | "let" OBJECT_IDENTIFIER ":" type "<-" expr "in" expr
        {
            $$ = new LetExprAst($2, $4, $6, $8);
        }
    | OBJECT_IDENTIFIER "<-" expr
        {
            $$ = new AssignExprAst($1, $3);
        }
    | "not" expr %prec UNOT
        {
            $$ = new UnaryOpExprAst("not", $2);
        }
    | "-" expr %prec UMINUS
        {
            $$ = new UnaryOpExprAst("-", $2);
        }
    | "isnull" expr %prec UISNULL
        {
            $$ = new UnaryOpExprAst("isnull", $2);
        }
    | expr "=" expr
        {
            $$ = new BinaryOpExprAst("=", $1, $3);
        }
    | expr "<" expr
        {
            $$ = new BinaryOpExprAst("<", $1, $3);
        }
    | expr "<=" expr
        {
            $$ = new BinaryOpExprAst("<=", $1, $3);
        }
    | expr "+" expr
        {
            $$ = new BinaryOpExprAst("+", $1, $3);
        }
    | expr "-" expr
        {
            $$ = new BinaryOpExprAst("-", $1, $3);
        }
    | expr "*" expr
        {
            $$ = new BinaryOpExprAst("*", $1, $3);
        }
    | expr "/" expr
        {
            $$ = new BinaryOpExprAst("/", $1, $3);
        }
    | expr "^" expr
        {
            $$ = new BinaryOpExprAst("^", $1, $3);
        }
    | expr "and" expr
        {
            $$ = new BinaryOpExprAst("and", $1, $3);
        }
    | OBJECT_IDENTIFIER "(" args ")"
        {
            CallExprAst* call = new CallExprAst(new SelfExprAst(), $1);
            call->arguments = $3;
            $$ = call;
        }
    | expr "." OBJECT_IDENTIFIER "(" args ")"
        {
            CallExprAst* call = new CallExprAst($1, $3);
            call->arguments = $5;
            $$ = call;
        }
    | "new" TYPE_IDENTIFIER
        {
            $$ = new NewExprAst($2);
        }
    | OBJECT_IDENTIFIER
        {
            $$ = new ObjectIdExprAst($1);
        }
    | "self"
        {
            $$ = new SelfExprAst();
        }
    | INTEGER_LITERAL
        {
            $$ = new IntegerLiteralExprAst($1);
        }
    | STRING_LITERAL
        {
            $$ = new StringLiteralExprAst($1);
        }
    | "true"
        {
            $$ = new BooleanLiteralExprAst(true);
        }
    | "false"
        {
            $$ = new BooleanLiteralExprAst(false);
        }
    | "(" ")"
        {
            $$ = new UnitExprAst();
        }
    | "(" expr ")"
        {
            $$ = $2;
        }
    | block
        {
            $$ = $1;
        }
    ;

// Method call arguments
args
    : /* empty */
        {
            $$ = std::vector<ExprAst*>();
        }
    | expr_list
        {
            $$ = $1;
        }
    ;

%%

// User code
void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    std::cerr   << *(pos.filename) << ":"
                << pos.line << ":" 
                << pos.column << ": "
                << m
                << std::endl;
}