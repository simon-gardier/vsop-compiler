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

// Grammar rules for part 2 start here ----------------------------------------
// Type declarations for non-terminals
%type <std::shared_ptr<Program>> program
%type <std::vector<std::shared_ptr<Class>>> class_list
%type <std::shared_ptr<Class>> class
%type <std::vector<std::shared_ptr<Field>>> field_list
%type <std::shared_ptr<Field>> field
%type <std::vector<std::shared_ptr<Method>>> method_list
%type <std::shared_ptr<Method>> method
%type <std::vector<std::shared_ptr<Formal>>> formal_list
%type <std::shared_ptr<Formal>> formal
%type <std::shared_ptr<Block>> block
%type <std::vector<std::shared_ptr<Expression>>> expr_list
%type <std::shared_ptr<Expression>> expr
%type <std::shared_ptr<Type>> type

// Operator precedence and associativity (lowest to highest)
%left "and"
%left "="
%left "<" "<="
%left "+" "-"
%left "*" "/"
%right "^"
%right "isnull"
%right "not"
%left "."

%%
// Grammar rules for part 2 starts here
program: class_list { 
    $$ = std::make_shared<Program>($1);
    driver.result = $$;
}

class_list: class class_list { 
    $2.insert($2.begin(), $1);
    $$ = $2;
}
| class { 
    $$ = std::vector<std::shared_ptr<Class>>{$1};
}

class: CLASS TYPE_IDENTIFIER EXTENDS TYPE_IDENTIFIER LBRACE field_list method_list RBRACE { 
    $$ = std::make_shared<Class>(@$, $2, $4, $6, $7);
}
| CLASS TYPE_IDENTIFIER LBRACE field_list method_list RBRACE { 
    $$ = std::make_shared<Class>(@$, $2, "Object", $4, $5);
}

field_list: field field_list { 
    $2.insert($2.begin(), $1);
    $$ = $2;
}
| /* empty */ { 
    $$ = std::vector<std::shared_ptr<Field>>{};
}

field: OBJECT_IDENTIFIER COLON type SEMICOLON { 
    $$ = std::make_shared<Field>(@$, $1, $3, nullptr);
}
| OBJECT_IDENTIFIER COLON type ASSIGN expr SEMICOLON { 
    $$ = std::make_shared<Field>(@$, $1, $3, $5);
}

method_list: method method_list { 
    $2.insert($2.begin(), $1);
    $$ = $2;
}
| /* empty */ { 
    $$ = std::vector<std::shared_ptr<Method>>{};
}

method: OBJECT_IDENTIFIER LPAR formal_list RPAR COLON type block { 
    $$ = std::make_shared<Method>(@$, $1, $3, $6, $7);
}
| OBJECT_IDENTIFIER LPAR RPAR COLON type block { 
    $$ = std::make_shared<Method>(@$, $1, std::vector<std::shared_ptr<Formal>>{}, $5, $6);
}

formal_list: formal COMMA formal_list { 
    $3.insert($3.begin(), $1);
    $$ = $3;
}
| formal { 
    $$ = std::vector<std::shared_ptr<Formal>>{$1};
}

formal: OBJECT_IDENTIFIER COLON type { 
    $$ = std::make_shared<Formal>(@$, $1, $3);
}

block: LBRACE expr_list RBRACE { 
    $$ = std::make_shared<Block>(@$, $2);
}

expr_list: expr SEMICOLON expr_list { 
    $3.insert($3.begin(), $1);
    $$ = $3;
}
| expr { 
    $$ = std::vector<std::shared_ptr<Expression>>{$1};
}

expr: IF expr THEN expr { 
    $$ = std::make_shared<If>(@$, $2, $4, nullptr);
}
| IF expr THEN expr ELSE expr { 
    $$ = std::make_shared<If>(@$, $2, $4, $6);
}
| WHILE expr DO expr { 
    $$ = std::make_shared<While>(@$, $2, $4);
}
| LET OBJECT_IDENTIFIER COLON type IN expr { 
    $$ = std::make_shared<Let>(@$, $2, $4, nullptr, $6);
}
| LET OBJECT_IDENTIFIER COLON type ASSIGN expr IN expr { 
    $$ = std::make_shared<Let>(@$, $2, $4, $6, $8);
}
| OBJECT_IDENTIFIER ASSIGN expr { 
    $$ = std::make_shared<Assign>(@$, $1, $3);
}
| NOT expr { 
    $$ = std::make_shared<UnaryOp>(@$, "not", $2);
}
| ISNULL expr { 
    $$ = std::make_shared<UnaryOp>(@$, "isnull", $2);
}
| MINUS expr { 
    $$ = std::make_shared<UnaryOp>(@$, "-", $2);
}
| expr AND expr { 
    $$ = std::make_shared<BinaryOp>(@$, "and", $1, $3);
}
| expr EQUAL expr { 
    $$ = std::make_shared<BinaryOp>(@$, "=", $1, $3);
}
| expr LOWER expr { 
    $$ = std::make_shared<BinaryOp>(@$, "<", $1, $3);
}
| expr LOWER_EQUAL expr { 
    $$ = std::make_shared<BinaryOp>(@$, "<=", $1, $3);
}
| expr PLUS expr { 
    $$ = std::make_shared<BinaryOp>(@$, "+", $1, $3);
}
| expr MINUS expr { 
    $$ = std::make_shared<BinaryOp>(@$, "-", $1, $3);
}
| expr TIMES expr { 
    $$ = std::make_shared<BinaryOp>(@$, "*", $1, $3);
}
| expr DIV expr { 
    $$ = std::make_shared<BinaryOp>(@$, "/", $1, $3);
}
| expr POW expr { 
    $$ = std::make_shared<BinaryOp>(@$, "^", $1, $3);
}
| expr DOT OBJECT_IDENTIFIER LPAR expr_list RPAR { 
    $$ = std::make_shared<Call>(@$, $1, $3, $5);
}
| expr DOT OBJECT_IDENTIFIER LPAR RPAR { 
    $$ = std::make_shared<Call>(@$, $1, $3, std::vector<std::shared_ptr<Expression>>{});
}
| OBJECT_IDENTIFIER LPAR expr_list RPAR { 
    $$ = std::make_shared<Call>(@$, std::make_shared<Self>(@$), $1, $3);
}
| OBJECT_IDENTIFIER LPAR RPAR { 
    $$ = std::make_shared<Call>(@$, std::make_shared<Self>(@$), $1, std::vector<std::shared_ptr<Expression>>{});
}
| NEW TYPE_IDENTIFIER { 
    $$ = std::make_shared<New>(@$, $2);
}
| OBJECT_IDENTIFIER { 
    $$ = std::make_shared<ObjectIdentifier>(@$, $1);
}
| SELF { 
    $$ = std::make_shared<Self>(@$);
}
| INTEGER_LITERAL { 
    $$ = std::make_shared<IntegerLiteral>(@$, $1);
}
| STRING_LITERAL { 
    $$ = std::make_shared<StringLiteral>(@$, $1);
}
| TRUE { 
    $$ = std::make_shared<BooleanLiteral>(@$, true);
}
| FALSE { 
    $$ = std::make_shared<BooleanLiteral>(@$, false);
}
| UNIT { 
    $$ = std::make_shared<Unit>(@$);
}
| LPAR expr RPAR { 
    $$ = $2;
}
| block { 
    $$ = $1;
}

type: INT32 { 
    $$ = std::make_shared<Type>(@$, "int32");
}
| BOOL { 
    $$ = std::make_shared<Type>(@$, "bool");
}
| STRING { 
    $$ = std::make_shared<Type>(@$, "string");
}
| UNIT { 
    $$ = std::make_shared<Type>(@$, "unit");
}
| TYPE_IDENTIFIER { 
    $$ = std::make_shared<Type>(@$, $1);
}
%%
// Grammar rules for part 2 ends here 
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
