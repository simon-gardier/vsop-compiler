/**
 * @brief Driver for VSOP compiler. Based on course example
 */
#include <iostream>
#include <string>
#include <map>
#include "driver.hpp"
#include "parser.hpp"
using namespace VSOP;

/**
 * @brief Map a token type to its string representation for prints.
 */
static const std::map<Parser::token_type, std::string> type_to_string = {
    {Parser::token::TYPE_IDENTIFIER,    "type-identifier"},
    {Parser::token::OBJECT_IDENTIFIER,  "object-identifier"},
    {Parser::token::STRING_LITERAL,     "string-literal"},
    {Parser::token::INTEGER_LITERAL,    "integer-literal"},
    // Operators
    {Parser::token::LBRACE,             "lbrace"},
    {Parser::token::RBRACE,             "rbrace"},
    {Parser::token::LPAR,               "lpar"},
    {Parser::token::RPAR,               "rpar"},
    {Parser::token::COLON,              "colon"},
    {Parser::token::SEMICOLON,          "semicolon"},
    {Parser::token::COMMA,              "comma"},
    {Parser::token::PLUS,               "plus"},
    {Parser::token::MINUS,              "minus"},
    {Parser::token::TIMES,              "times"},
    {Parser::token::DIV,                "div"},
    {Parser::token::POW,                "pow"},
    {Parser::token::DOT,                "dot"},
    {Parser::token::EQUAL,              "equal"},
    {Parser::token::LOWER,              "lower"},
    {Parser::token::LOWER_EQUAL,        "lower-equal"},
    {Parser::token::ASSIGN,             "assign"},
    {Parser::token::AND,                "and"},
    //Keywords
    {Parser::token::BOOL,               "bool"},
    {Parser::token::CLASS,              "class"},
    {Parser::token::DO,                 "do"},
    {Parser::token::ELSE,               "else"},
    {Parser::token::EXTENDS,            "extends"},
    {Parser::token::FALSE,              "false"},
    {Parser::token::IF,                 "if"},
    {Parser::token::IN,                 "in"},
    {Parser::token::INT32,              "int32"},
    {Parser::token::ISNULL,             "isnull"},
    {Parser::token::LET,                "let"},
    {Parser::token::NEW,                "new"},
    {Parser::token::NOT,                "not"},
    {Parser::token::SELF,               "self"},
    {Parser::token::STRING,             "string"},
    {Parser::token::THEN,               "then"},
    {Parser::token::TRUE,               "true"},
    {Parser::token::UNIT,               "unit"},
    {Parser::token::WHILE,              "while"}
};

/**
 * @brief Print the information about a token
 *
 * @param token the token
 */
static void print_token(Parser::symbol_type token)
{
    position pos = token.location.begin;
    Parser::token_type type = (Parser::token_type)token.type_get();

    std::cout   << pos.line << ","
                << pos.column << ","
                << type_to_string.at(type);

    if( type == Parser::token::TYPE_IDENTIFIER || 
        type == Parser::token::OBJECT_IDENTIFIER)
    {
        std::string value = token.value.as<std::string>();
        std::cout << "," << value;
    }
    else if (type == Parser::token::STRING_LITERAL)
    {
        std::string value = token.value.as<std::string>();
        std::cout << "," << "\"" << value << "\"";
    }
    else if (type == Parser::token::INTEGER_LITERAL)
    {
        int value = token.value.as<int>();
        std::cout << "," << value;
    }
    std::cout << std::endl;
}

/**
 * @brief Lex the source_file and fill a vector with the tokens found
 * 
 * @return int 0 if no lexing error found, 1 else
 */
int Driver::lex()
{
    scan_begin();
    int error = 0;
    while (true)
    {
        Parser::symbol_type token = yylex();
        if ((Parser::token_type)token.type_get() == Parser::token::YYEOF)
            break;
        if ((Parser::token_type)token.type_get() != Parser::token::YYerror)
            tokens.push_back(token);
        else
        {
            error = 1;
            break;
        }
    }
    scan_end();
    return error;
}

/**
 * @brief Parse the source_file and build the AST
 * 
 * @return int 0 if no parsing error, 1 else 
 */
int Driver::parse()
{
    // Initialize the parser
    scan_begin();
    Parser parser(*this);
    int result = parser.parse();
    scan_end();

    if (result == 0 && programAst) {
        // Perform semantic analysis
        semanticAnalyzer = std::make_unique<SemanticAnalyzer>(source_file);
        if (!semanticAnalyzer->analyze(programAst.get())) {
            // Print semantic errors
            for (const auto& error : semanticAnalyzer->getErrors()) {
                std::cerr << error << std::endl;
            }
            return 1;
        }
    }

    return result;
}

/**
 * @brief Parse the source_file and build the AST without semantic analysis
 * 
 * @return int 0 if no parsing error, 1 else 
 */
int Driver::parseWithoutSemantic()
{
    // Initialize the parser
    scan_begin();
    Parser parser(*this);
    int result = parser.parse();
    scan_end();

    return result;
}

/**
 * @brief Prints all the tokens that have been pushed in the vector tokens
 * 
 */
void Driver::print_tokens()
{
    for (auto token : tokens)
        print_token(token);
}
