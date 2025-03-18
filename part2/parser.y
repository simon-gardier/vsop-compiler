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


%nterm program 
%nterm <ClassAst*> class 
%nterm <FieldAst*> field 
%nterm <MethodAst*> method 
%nterm <std::vector<FormalAst*>> formals 
%nterm <FormalAst*> formal 
%nterm <ExprAst*> expr if while let object-assign unop binop call new
%nterm <ExprBlockAst*> block 
%nterm <std::string> type 
%nterm <ExprLiteralAst*> literal

%nterm <std::vector<ClassAst*>> classes
%nterm <ClassBody> class-body // array Ast-list[2] - fields and methods
%nterm <std::vector<ExprAst*>> exprs args args-optional


// Precedence
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

program: // AST-list
    classes { driver.programAst = std::make_unique<ProgramAst>(@1.begin.line, @1.begin.column, $1); }
   
classes:
    class           { $$.push_back($1); }
    | classes class { $1.push_back($2); $$ = $1; }

class: // AST-function
    CLASS TYPE_ID LBRACE class-body RBRACE { $$ = new ClassAst(@1.begin.line, @1.begin.column, $2, "Object", $4.fields, $4.methods); };
    | CLASS TYPE_ID EXTENDS TYPE_ID LBRACE class-body RBRACE { $$ = new ClassAst(@1.begin.line, @1.begin.column, $2, $4, $6.fields, $6.methods); };

class-body: // array[2] of AST-list
    %empty              {}
    | class-body field  { $1.fields.push_back($2); $$ = $1; }
    | class-body method { $1.methods.push_back($2); $$ = $1; };

field: // AST-function
    OBJECT_ID COLON type SEMICOLON { $$ = new FieldAst(@1.begin.line, @1.begin.column, $1, $3); };
    | OBJECT_ID COLON type ASSIGN expr SEMICOLON { $$ = new FieldAst(@1.begin.line, @1.begin.column, $1, $3, $5); };

method: // AST-function
    OBJECT_ID LPAR formals RPAR COLON type block { $$ = new MethodAst(@1.begin.line, @1.begin.column, $1, $3, $6, $7); };

type: // AST-data
    INT32      { $$ = "int32"; }
    | BOOL     { $$ = "bool"; }
    | STRING   { $$ = "string"; }
    | UNIT     { $$ = "unit"; }
    | TYPE_ID  { $$ = $1; };

formals: // AST-list
    %empty                 {}
    | formal               { $$.push_back($1); }
    | formals COMMA formal { $1.push_back($3); $$ = $1; };

formal: // AST-typed
    OBJECT_ID COLON type { $$ = new FormalAst(@1.begin.line, @1.begin.column, $1, $3); };

block: // AST-list
    LBRACE exprs RBRACE { $$ = new ExprBlockAst(@1.begin.line, @1.begin.column, $2); };

exprs:  // AST-list
    expr                   { $$.push_back($1); }
    | exprs SEMICOLON expr { $1.push_back($3); $$ = $1; };

expr: // AST-optional
    if                  
    | while             
    | let               
    | object-assign     
    | unop              
    | binop             
    | call              
    | new               { $$ = $1; };

expr:
    SELF                { $$ = new ExprObjectIdAst(@1.begin.line, @1.begin.column, "self"); }
    | OBJECT_ID         { $$ = new ExprObjectIdAst(@1.begin.line, @1.begin.column, $1); }
    | literal           { $$ = $1; }
    | LPAR RPAR         { $$ = new ExprLiteralAst(@1.begin.line, @1.begin.column, "()", "unit"); }
    | LPAR expr RPAR    { $$ = $2; }
    
expr:
    block             { $$ = $1; };

args-optional: // AST-list
    %empty {}
    | args { $$ = $1; };

args: // AST-list
    expr              { $$.push_back($1); }
    | args COMMA expr { $1.push_back($3); $$ = $1; };

if: // AST-function
    IF expr THEN expr { $$ = new ExprIfAst(@1.begin.line, @1.begin.column, $2, $4); };
    | IF expr THEN expr ELSE expr { $$ = new ExprIfAst(@1.begin.line, @1.begin.column, $2, $4, $6); };

while: // AST-function
    WHILE expr DO expr { $$ = new ExprWhileAst(@1.begin.line, @1.begin.column, $2, $4); };

let: // AST-function
    LET OBJECT_ID COLON type IN expr { $$ = new ExprLetAst(@1.begin.line, @1.begin.column, $2, $4, $6); };
    | LET OBJECT_ID COLON type ASSIGN expr IN expr { $$ = new ExprLetAst(@1.begin.line, @1.begin.column, $2, $4, $6, $8); };

object-assign: // AST-function
    OBJECT_ID ASSIGN expr { $$ = new ExprAssignAst(@1.begin.line, @1.begin.column, $1, $3); };

unop: // AST-function
    NOT expr      { $$ = new ExprUnopAst(@1.begin.line, @1.begin.column, "not", $2); }
    | MINUS expr  { $$ = new ExprUnopAst(@1.begin.line, @1.begin.column, "-", $2); }
    | ISNULL expr { $$ = new ExprUnopAst(@1.begin.line, @1.begin.column, "isnull", $2); };

binop: // AST-function
    expr PLUS expr %prec PLUS                 { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "+", $1, $3); }
    | expr EQUAL expr %prec EQUAL             { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "=", $1, $3); }
    | expr LOWER expr %prec LOWER             { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "<", $1, $3); }
    | expr LOWER_EQUAL expr %prec LOWER_EQUAL { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "<=", $1, $3); }
    | expr MINUS expr %prec MINUS             { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "-", $1, $3); }
    | expr TIMES expr %prec TIMES             { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "*", $1, $3); }
    | expr DIV expr %prec DIV                 { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "/", $1, $3); }
    | expr POW expr %prec POW                 { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "^", $1, $3); }
    | expr AND expr %prec AND                 { $$ = new ExprBinopAst(@1.begin.line, @1.begin.column, "and", $1, $3); };

call: // AST-function
    OBJECT_ID LPAR args-optional RPAR            { $$ = new ExprCallAst(@1.begin.line, @1.begin.column, new ExprObjectIdAst(@1.begin.line, @1.begin.column, "self"), $1, $3); } 
    | expr DOT OBJECT_ID LPAR args-optional RPAR { $$ = new ExprCallAst(@1.begin.line, @1.begin.column, $1, $3, $5); };

new: // AST-function
    NEW TYPE_ID { $$ = new ExprNewAst(@1.begin.line, @1.begin.column, $2); };

literal: // AST-data
    INTEGER_LIT  { $$ = new ExprLiteralAst(@1.begin.line, @1.begin.column, std::to_string($1), "int32"); }
    | STRING_LIT { $$ = new ExprLiteralAst(@1.begin.line, @1.begin.column, $1, "string"); }
    | TRUE       { $$ = new ExprLiteralAst(@1.begin.line, @1.begin.column, "true", "bool"); }
    | FALSE      { $$ = new ExprLiteralAst(@1.begin.line, @1.begin.column, "false", "bool"); };


%%
// User code
void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    cerr << *(pos.filename) << ":"
         << pos.line << ":" 
         << pos.column << ": "
         << m
         << endl;
}