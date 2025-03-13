/**
 * @brief lexer implementation for VSOP compiler. Based on course example
 */
%{
    #include <string>
    #include <iostream>
    #include <sstream>
    #include <iomanip>
    #include <stack>
    #include "parser.hpp"
    #include "driver.hpp"
    using namespace VSOP;
    // Global variable used to maintain the current location.
    location loc;
    location string_start;
    std::stack<location> comments_start;
    // Global variable used to maintain of a String when encountered.
    static std::string string_buf;
    // Error function
    static void print_error(const position &pos, const std::string &m);
    // Code run each time a pattern is matched, prior to the execution of the code related to the pattern.
    static void update_location(const char *text, int len, location &loc);
    #define YY_USER_ACTION  update_location(yytext, yyleng, loc);
%}

/** Flex options
 * - noyywrap: yylex will not call yywrap() function
 * - nounput: do not generate yyunput() function
 * - noinput: do not generate yyinput() function
 * - batch: tell Flex that the lexer will not often be used interactively
 */
%option noyywrap nounput noinput batch

/** Custom states
 *  - STRING: state for string rules 
 *  - COMMENT: state for comments rules
 */
%x STRING COMMENT

/* Regex definitions */
type_identifier     [A-Z][a-zA-Z_0-9]*
object_identifier   [a-z][a-zA-Z_0-9]*
int_literal         [0-9]+
hex_literal         "0x"[0-9a-fA-F]+
invalid_int_reminder    [a-zA-Z_]
invalid_hex_reminder    [g-zG-Z_]
blank               [ \b\t\r]
newline             \n
esc_seq             \\[btnr"\\]|\\x[0-9a-fA-F]{2}

%%
    /* White spaces rules */
{blank}+        { }
{newline}+      { }
    /* Single line comments rule */
"//".*          { }
    /* Integer literals rules */
{int_literal}{invalid_int_reminder}+    { print_error(loc.begin, "invalid integer literal in [" + std::string(yytext) + "]");   return Parser::make_YYerror(loc); }
{hex_literal}{invalid_hex_reminder}+    { print_error(loc.begin, "invalid integer (hexa) literal in [" + std::string(yytext) + "]"); return Parser::make_YYerror(loc); }
{int_literal}|{hex_literal}             { long value = std::stoi(yytext, nullptr, yytext[0] == '0' && yytext[1] == 'x' ? 16 : 10); return Parser::make_INTEGER_LITERAL(value, loc); }

    /* Comments rules */
"(*"            { comments_start.push(loc); BEGIN(COMMENT); }
<COMMENT>"(*"   { comments_start.push(loc); }
<COMMENT>"*)"   { comments_start.pop(); if (comments_start.empty()) BEGIN(INITIAL); }
<COMMENT>\n     { }
<COMMENT>.      { }
<COMMENT><<EOF>> { print_error(comments_start.top().begin, "Multi line comment must be terminated before EOF"); BEGIN(INITIAL); return Parser::make_YYerror(loc); }

    /* String literals rules */
"\""            { string_buf.clear(); string_start = loc; BEGIN(STRING); }

<STRING>"\""    { BEGIN(INITIAL); return Parser::make_STRING_LITERAL(string_buf, string_start); }
<STRING>\n      { print_error(loc.begin, "\\n is forbiden in string"); BEGIN(INITIAL); return Parser::make_YYerror(loc); }
<STRING>\\[ \b\t\r]*\n[ \b\t\r]*  { }
<STRING>{esc_seq} { switch (yytext[1]) {
                        case 'b': string_buf += "\\x08"; break;
                        case 't': string_buf += "\\x09"; break;
                        case 'n': string_buf += "\\x0a"; break;
                        case 'r': string_buf += "\\x0d"; break;
                        case '"': string_buf += "\\x22"; break;
                        case '\\': string_buf += "\\x5c"; break;
                        default: string_buf += yytext; break;
                    }
                }
<STRING>\\.     { print_error(loc.begin, "unknown escape sequence starting with: '"+ std::string(1, yytext[1])+"'"); BEGIN(INITIAL); return Parser::make_YYerror(loc); }
<STRING>.       { string_buf += yytext[0]; }
<STRING><<EOF>> { print_error(string_start.begin, "string must be terminated before EOF"); BEGIN(INITIAL); return Parser::make_YYerror(loc); }

    /* Operators rules */
"}"             return Parser::make_RBRACE(loc); 
"("             return Parser::make_LPAR(loc); 
")"             return Parser::make_RPAR(loc);
":"             return Parser::make_COLON(loc);
"{"             return Parser::make_LBRACE(loc);
";"             return Parser::make_SEMICOLON(loc);
","             return Parser::make_COMMA(loc);
"+"             return Parser::make_PLUS(loc);
"-"             return Parser::make_MINUS(loc);
"*"             return Parser::make_TIMES(loc);
"/"             return Parser::make_DIV(loc);
"^"             return Parser::make_POW(loc);
"."             return Parser::make_DOT(loc);
"="             return Parser::make_EQUAL(loc);
"<"             return Parser::make_LOWER(loc);
"<="            return Parser::make_LOWER_EQUAL(loc);
"<-"            return Parser::make_ASSIGN(loc);
    /* Keywords rules */
"and"           return Parser::make_AND(loc);
"bool"          return Parser::make_BOOL(loc);
"class"         return Parser::make_CLASS(loc);
"do"            return Parser::make_DO(loc);
"else"          return Parser::make_ELSE(loc);
"extends"       return Parser::make_EXTENDS(loc);
"false"         return Parser::make_FALSE(loc);
"if"            return Parser::make_IF(loc);
"in"            return Parser::make_IN(loc);
"int32"         return Parser::make_INT32(loc);
"isnull"        return Parser::make_ISNULL(loc);
"let"           return Parser::make_LET(loc);
"new"           return Parser::make_NEW(loc);
"not"           return Parser::make_NOT(loc);
"self"          return Parser::make_SELF(loc);
"string"        return Parser::make_STRING(loc);
"then"          return Parser::make_THEN(loc);
"true"          return Parser::make_TRUE(loc);
"unit"          return Parser::make_UNIT(loc);
"while"         return Parser::make_WHILE(loc);
    /* Identifiers rules */
{type_identifier}   { return Parser::make_TYPE_IDENTIFIER(yytext, loc); }
{object_identifier} { return Parser::make_OBJECT_IDENTIFIER(yytext, loc); }
    /* Invalid characters*/
.               { print_error(loc.begin, "invalid character: " + std::string(yytext)); return Parser::make_YYerror(loc); }
<<EOF>>         { return Parser::make_YYEOF(loc); }

%%

/**
 * @brief print error m on error std output
 * 
 * @param pos position of the error
 * @param m message of the error
 */
static void print_error(const position &pos, const std::string &m)
{
    std::cerr   << *(pos.filename) << ":"
                << pos.line << ":"
                << pos.column << ":"
                << " lexical error: "
                << m
                << std::endl;
}

/**
 * @brief Update the location begin (with .step()) and end (with the loop)
 * 
 * @param text the matching rule text for which we want to adjust loc
 * @param len the length of the text
 * @param loc the location variable used to move in the source file
 */
static void update_location(const char *text, int len, location &loc) {
    loc.step();
    for (int i = 0; i < len; ++i) {
        if (text[i] == '\n') {
            loc.lines(1);
        } else {
            loc.columns(1);
        }
    }
}

/**
 * @brief Close source file
 * 
 */
void Driver::scan_end()
{
    fclose(yyin);
}

/**
 * @brief Open source file. Print error on std error output if open fails.
 * 
 */
void Driver::scan_begin()
{
    loc.initialize(&source_file);

    if (source_file.empty() || source_file == "-")
        yyin = stdin;
    else if (!(yyin = fopen(source_file.c_str(), "r")))
    {
        std::cerr << "cannot open " << source_file << ": " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
}
