/* This flex/bison example is provided to you as a starting point for your
 * assignment. You are free to use its code in your project.
 *
 * This example implements a simple calculator. You can use the '-l' flag to
 * list all the tokens found in the source file, and the '-p' flag (or no flag)
 * to parse the file and to compute the result.
 *
 * Also, if you have any suggestions for improvements, please let us know.
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

// C++ code put inside header file
%code requires {
    #include <string>
    #include <vector>
    #include <array>
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

    using namespace std;
}

// Token and symbols definitions
%token
    LBRACE      "{"
    RBRACE      "}"
    LPAR        "("
    RPAR        ")"
    COLON       ":"
    SEMICOLON   ";"
    COMMA       ","
    PLUS        "+"
    MINUS       "-"
    TIMES       "*"
    DIV         "/"
    POW         "^"
    DOT         "."
    EQUAL       "="
    LOWER       "<"
    LOWER_EQUAL "<="
    ASSIGN      "<-"
    AND         "and"
    BOOL        "bool"
    CLASS       "class"
    DO          "do"
    ELSE        "else"
    EXTENDS     "extends"
    FALSE       "false"
    IF          "if"
    IN          "in"
    INT32       "int32"
    ISNULL      "isnull"
    LET         "let"
    NEW         "new"
    NOT         "not"
    SELF        "self"
    STRING      "string"
    THEN        "then"
    TRUE        "true"
    UNIT        "unit"
    WHILE       "while"
;

%define parse.error verbose

// For some symbols, need to store a value
%token <std::string> 
    TYPE_ID    "type-identifier"
    OBJECT_ID  "object-identifier"
    STRING_LIT "string-literal"
    ERROR      "error"
;

%token <int> INTEGER_LIT        "integer-literal"

// Type declarations for non-terminals
%type <std::vector<ClassDef*>> program class-list
%type <ClassDef*> single-class
%type <ClassMembers> members
%type <FieldDef*> field-decl
%type <MethodDef*> method-decl
%type <std::string> type-spec
%type <std::vector<Parameter*>> param-list
%type <Parameter*> single-param
%type <CompoundExpr*> code-block
%type <std::vector<Expression*>> expr-sequence arg-list arg-list-opt
%type <Expression*> single-expr conditional loop variable-binding assignment unary-op binary-op method-call object-creation
%type <LiteralExpr*> constant

%right ASSIGN
%left AND
%right NOT
%nonassoc LOWER LOWER_EQUAL EQUAL
%left "+" "-"; // Could also do: %left PLUS MINUS
%left "*" "/";
%right ISNULL
%right POW
%left DOT

%%
// Grammar rules

%start program;

// Program is the root node
program: 
    class-list { driver.programAst = std::make_unique<Program>(@1.begin.line, @1.begin.column, $1); $$ = $1; }
;

// One or more class definitions
class-list:
    single-class                { $$.push_back($1); }
    | class-list single-class   { $1.push_back($2); $$ = $1; }
;

// A class definition with optional parent
single-class:
    CLASS TYPE_ID LBRACE members RBRACE 
        { $$ = new ClassDef(@1.begin.line, @1.begin.column, $2, "Object", $4.fields, $4.methods); }
    | CLASS TYPE_ID EXTENDS TYPE_ID LBRACE members RBRACE 
        { $$ = new ClassDef(@1.begin.line, @1.begin.column, $2, $4, $6.fields, $6.methods); }
;

// Class members (fields and methods)
members:
    %empty                { }
    | members field-decl  { $1.fields.push_back($2); $$ = $1; }
    | members method-decl { $1.methods.push_back($2); $$ = $1; }
;

// Field declaration with optional initialization
field-decl:
    OBJECT_ID COLON type-spec SEMICOLON 
        { $$ = new FieldDef(@1.begin.line, @1.begin.column, $1, $3); }
    | OBJECT_ID COLON type-spec ASSIGN single-expr SEMICOLON 
        { $$ = new FieldDef(@1.begin.line, @1.begin.column, $1, $3, $5); }
;

// Method declaration
method-decl:
    OBJECT_ID LPAR param-list RPAR COLON type-spec code-block 
        { $$ = new MethodDef(@1.begin.line, @1.begin.column, $1, $3, $6, $7); }
;

// Type specification
type-spec:
    INT32      { $$ = "int32"; }
    | BOOL     { $$ = "bool"; }
    | STRING   { $$ = "string"; }
    | UNIT     { $$ = "unit"; }
    | TYPE_ID  { $$ = $1; }
;

// Method parameters
param-list:
    %empty                    { }
    | single-param           { $$.push_back($1); }
    | param-list COMMA single-param { $1.push_back($3); $$ = $1; }
;

// Single parameter declaration
single-param:
    OBJECT_ID COLON type-spec { $$ = new Parameter(@1.begin.line, @1.begin.column, $1, $3); }
;

// Block of expressions
code-block:
    LBRACE expr-sequence RBRACE { $$ = new CompoundExpr(@1.begin.line, @1.begin.column, $2); }
;

// Sequence of expressions
expr-sequence:
    single-expr                      { $$.push_back($1); }
    | expr-sequence SEMICOLON single-expr { $1.push_back($3); $$ = $1; }
;

// Expression types
single-expr:
    conditional
    | loop
    | variable-binding
    | assignment
    | unary-op
    | binary-op
    | method-call
    | object-creation { $$ = $1; }
;

// Basic expressions
single-expr:
    SELF                { $$ = new IdentifierExpr(@1.begin.line, @1.begin.column, "self"); }
    | OBJECT_ID         { $$ = new IdentifierExpr(@1.begin.line, @1.begin.column, $1); }
    | constant          { $$ = $1; }
    | LPAR RPAR         { $$ = new LiteralExpr(@1.begin.line, @1.begin.column, "()", "unit"); }
    | LPAR single-expr RPAR    { $$ = $2; }
;

// Block as expression
single-expr:
    code-block { $$ = $1; }
;

// Optional argument list
arg-list-opt:
    %empty { }
    | arg-list { $$ = $1; }
;

// Argument list
arg-list:
    single-expr                  { $$.push_back($1); }
    | arg-list COMMA single-expr { $1.push_back($3); $$ = $1; }
;

// Conditional expression
conditional:
    IF single-expr THEN single-expr 
        { $$ = new ConditionalExpr(@1.begin.line, @1.begin.column, $2, $4); }
    | IF single-expr THEN single-expr ELSE single-expr 
        { $$ = new ConditionalExpr(@1.begin.line, @1.begin.column, $2, $4, $6); }
;

// Loop expression
loop:
    WHILE single-expr DO single-expr { $$ = new LoopExpr(@1.begin.line, @1.begin.column, $2, $4); }
;

// Variable binding
variable-binding:
    LET OBJECT_ID COLON type-spec IN single-expr 
        { $$ = new VarDeclExpr(@1.begin.line, @1.begin.column, $2, $4, nullptr, $6); }
    | LET OBJECT_ID COLON type-spec ASSIGN single-expr IN single-expr 
        { $$ = new VarDeclExpr(@1.begin.line, @1.begin.column, $2, $4, $6, $8); }
;

// Assignment
assignment:
    OBJECT_ID ASSIGN single-expr { $$ = new AssignmentExpr(@1.begin.line, @1.begin.column, $1, $3); }
;

// Unary operations
unary-op:
    NOT single-expr      { $$ = new UnaryOpExpr(@1.begin.line, @1.begin.column, "not", $2); }
    | MINUS single-expr  { $$ = new UnaryOpExpr(@1.begin.line, @1.begin.column, "-", $2); }
    | ISNULL single-expr { $$ = new UnaryOpExpr(@1.begin.line, @1.begin.column, "isnull", $2); }
;

// Binary operations
binary-op:
    single-expr PLUS single-expr        { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "+", $1, $3); }
    | single-expr EQUAL single-expr     { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "=", $1, $3); }
    | single-expr LOWER single-expr     { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "<", $1, $3); }
    | single-expr LOWER_EQUAL single-expr { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "<=", $1, $3); }
    | single-expr MINUS single-expr     { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "-", $1, $3); }
    | single-expr TIMES single-expr     { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "*", $1, $3); }
    | single-expr DIV single-expr       { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "/", $1, $3); }
    | single-expr POW single-expr       { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "^", $1, $3); }
    | single-expr AND single-expr       { $$ = new BinaryOpExpr(@1.begin.line, @1.begin.column, "and", $1, $3); }
;

// Method invocation
method-call:
    OBJECT_ID LPAR arg-list-opt RPAR            
        { $$ = new MethodCallExpr(@1.begin.line, @1.begin.column, new IdentifierExpr(@1.begin.line, @1.begin.column, "self"), $1, $3); }
    | single-expr DOT OBJECT_ID LPAR arg-list-opt RPAR 
        { $$ = new MethodCallExpr(@1.begin.line, @1.begin.column, $1, $3, $5); }
;

// Object instantiation
object-creation:
    NEW TYPE_ID { $$ = new NewObjectExpr(@1.begin.line, @1.begin.column, $2); }
;

// Constants
constant:
    INTEGER_LIT  { $$ = new LiteralExpr(@1.begin.line, @1.begin.column, std::to_string($1), "int32"); }
    | STRING_LIT { $$ = new LiteralExpr(@1.begin.line, @1.begin.column, $1, "string"); }
    | TRUE       { $$ = new LiteralExpr(@1.begin.line, @1.begin.column, "true", "bool"); }
    | FALSE      { $$ = new LiteralExpr(@1.begin.line, @1.begin.column, "false", "bool"); }
;
%%
// User code
void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;
    std::cerr << *(pos.filename) << ":" << pos.line << ":" << pos.column << ": " << m << std::endl;
}