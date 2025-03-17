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
    
    // If we want to use the hardcoded example instead of parsing, uncomment this section
    /*
    // Create a sample AST based on the example
    programAst = std::make_unique<ProgramAst>();
    
    // Create List class
    ClassAst* listClass = new ClassAst("List");
    
    // isNil method
    MethodAst* isNilMethod = new MethodAst("isNil", "bool", new BooleanLiteralExprAst(true));
    listClass->methods.push_back(isNilMethod);
    
    // length method
    MethodAst* lengthMethod = new MethodAst("length", "int32", new IntegerLiteralExprAst(0));
    listClass->methods.push_back(lengthMethod);
    
    programAst->classes.push_back(listClass);
    
    // Create Nil class
    ClassAst* nilClass = new ClassAst("Nil", "List");
    programAst->classes.push_back(nilClass);
    
    // Create Cons class
    ClassAst* consClass = new ClassAst("Cons", "List");
    
    // Add fields
    FieldAst* headField = new FieldAst("head", "int32");
    FieldAst* tailField = new FieldAst("tail", "List");
    consClass->fields.push_back(headField);
    consClass->fields.push_back(tailField);
    
    // init method
    MethodAst* initMethod = new MethodAst("init", "Cons", nullptr);
    
    // Add formals
    FormalAst* hdFormal = new FormalAst("hd", "int32");
    FormalAst* tlFormal = new FormalAst("tl", "List");
    initMethod->formals.push_back(hdFormal);
    initMethod->formals.push_back(tlFormal);
    
    // Create method body
    BlockExprAst* initBody = new BlockExprAst();
    initBody->expressions.push_back(new AssignExprAst("head", new ObjectIdExprAst("hd")));
    initBody->expressions.push_back(new AssignExprAst("tail", new ObjectIdExprAst("tl")));
    initBody->expressions.push_back(new SelfExprAst());
    initMethod->body = initBody;
    
    consClass->methods.push_back(initMethod);
    
    // head method
    MethodAst* headMethod = new MethodAst("head", "int32", new ObjectIdExprAst("head"));
    consClass->methods.push_back(headMethod);
    
    // isNil method for Cons
    MethodAst* consIsNilMethod = new MethodAst("isNil", "bool", new BooleanLiteralExprAst(false));
    consClass->methods.push_back(consIsNilMethod);
    
    // length method for Cons
    CallExprAst* tailLengthCall = new CallExprAst(new ObjectIdExprAst("tail"), "length");
    BinaryOpExprAst* lengthExpr = new BinaryOpExprAst("+", new IntegerLiteralExprAst(1), tailLengthCall);
    MethodAst* consLengthMethod = new MethodAst("length", "int32", lengthExpr);
    consClass->methods.push_back(consLengthMethod);
    
    programAst->classes.push_back(consClass);
    
    // Create Main class
    ClassAst* mainClass = new ClassAst("Main");
    
    // main method
    MethodAst* mainMethod = new MethodAst("main", "int32", nullptr);
    
    // Create complex expression for main method
    NewExprAst* newNil = new NewExprAst("Nil");
    
    CallExprAst* innerInit = new CallExprAst(new NewExprAst("Cons"), "init");
    innerInit->arguments.push_back(new IntegerLiteralExprAst(2));
    innerInit->arguments.push_back(newNil);
    
    CallExprAst* middleInit = new CallExprAst(new NewExprAst("Cons"), "init");
    middleInit->arguments.push_back(new IntegerLiteralExprAst(1));
    middleInit->arguments.push_back(innerInit);
    
    CallExprAst* outerInit = new CallExprAst(new NewExprAst("Cons"), "init");
    outerInit->arguments.push_back(new IntegerLiteralExprAst(0));
    outerInit->arguments.push_back(middleInit);
    
    LetExprAst* letExpr = new LetExprAst("xs", "List", outerInit, nullptr);
    
    BlockExprAst* mainBody = new BlockExprAst();
    
    CallExprAst* printCall = new CallExprAst(new SelfExprAst(), "print");
    printCall->arguments.push_back(new StringLiteralExprAst("List has length "));
    mainBody->expressions.push_back(printCall);
    
    CallExprAst* lengthCall = new CallExprAst(new ObjectIdExprAst("xs"), "length");
    CallExprAst* printIntCall = new CallExprAst(new SelfExprAst(), "printInt32");
    printIntCall->arguments.push_back(lengthCall);
    mainBody->expressions.push_back(printIntCall);
    
    CallExprAst* printNewlineCall = new CallExprAst(new SelfExprAst(), "print");
    printNewlineCall->arguments.push_back(new StringLiteralExprAst("\n"));
    mainBody->expressions.push_back(printNewlineCall);
    
    mainBody->expressions.push_back(new IntegerLiteralExprAst(0));
    
    letExpr->scopeExpr = mainBody;
    mainMethod->body = letExpr;
    
    mainClass->methods.push_back(mainMethod);
    programAst->classes.push_back(mainClass);
    */
    
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