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
%type <int> expr
%type <std::string> type formal formal_list block field_list field method method_list class class_list program

// Operator precedence and associativity (lowest to highest)
%left "and"
%left "="
%left "<" "<="
%left "+" "-"
%left "*" "/"
%left "isnull"
%left "not"
%left "."

%%
// Grammar rules
program:
    class_list                  { /* Program consists of a list of classes */ }
    ;

class_list:
    class                       { /* Single class */ }
    | class_list class         { /* Multiple classes */ }
    ;

class:
    "class" TYPE_IDENTIFIER "{" field_list method_list "}"  { /* Class definition */ }
    | "class" TYPE_IDENTIFIER "extends" TYPE_IDENTIFIER "{" field_list method_list "}"  { /* Class with inheritance */ }
    ;

field_list:
    %empty                     { /* Empty field list */ }
    | field_list field        { /* List of fields */ }
    ;

field:
    OBJECT_IDENTIFIER ":" type "<-" expr ";"  { /* Field with initialization */ }
    | OBJECT_IDENTIFIER ":" type ";"          { /* Field without initialization */ }
    ;

method_list:
    %empty                     { /* Empty method list */ }
    | method_list method      { /* List of methods */ }
    ;

method:
    OBJECT_IDENTIFIER "(" formal_list ")" ":" type block  { /* Method definition */ }
    ;

formal_list:
    %empty                     { /* Empty formal list */ }
    | formal                   { /* Single formal */ }
    | formal_list "," formal   { /* Multiple formals */ }
    ;

formal:
    OBJECT_IDENTIFIER ":" type  { /* Formal parameter */ }
    ;

type:
    "int32"                    { /* Integer type */ }
    | "bool"                   { /* Boolean type */ }
    | "string"                 { /* String type */ }
    | "unit"                   { /* Unit type */ }
    | TYPE_IDENTIFIER         { /* User-defined type */ }
    ;

block:
    "{" expr "}"              { /* Single expression block */ }
    ;

expr:
    INTEGER_LITERAL           { /* Integer literal */ }
    | STRING_LITERAL         { /* String literal */ }
    | "true"                 { /* Boolean true */ }
    | "false"                { /* Boolean false */ }
    | OBJECT_IDENTIFIER      { /* Object identifier */ }
    | "self"                 { /* Self reference */ }
    | "(" expr ")"           { /* Parenthesized expression */ }
    | "not" expr             { /* Logical not */ }
    | expr "and" expr        { /* Logical and */ }
    | expr "=" expr          { /* Equality */ }
    | expr "<" expr          { /* Less than */ }
    | expr "<=" expr         { /* Less than or equal */ }
    | expr "+" expr          { /* Addition */ }
    | expr "-" expr          { /* Subtraction */ }
    | expr "*" expr          { /* Multiplication */ }
    | expr "/" expr          { /* Division */ }
    | expr "^" expr          { /* Power */ }
    | "-" expr               { /* Unary minus */ }
    | "isnull" expr          { /* Null test */ }
    | "while" expr "do" expr { /* While loop */ }
    | "if" expr "then" expr  { /* If-then */ }
    | "if" expr "then" expr "else" expr  { /* If-then-else */ }
    | "let" OBJECT_IDENTIFIER ":" type "<-" expr "in" expr  { /* Let binding */ }
    | OBJECT_IDENTIFIER "<-" expr  { /* Assignment */ }
    | expr "." OBJECT_IDENTIFIER "(" ")"  { /* Method call without arguments */ }
    | expr "." OBJECT_IDENTIFIER "(" expr ")"  { /* Method call with one argument */ }
    | "new" TYPE_IDENTIFIER   { /* Object creation */ }
    | block                   { /* Block expression */ }
    ;
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
