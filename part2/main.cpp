/**
 * @brief Main program for VSOP compiler. Options -l : lex source code, -p : parse source code
 */

#include <iostream>
#include <string>

#include "driver.hpp"
#include "ast.hpp"

using namespace std;

// Adapted from https://www.gnu.org/software/bison/manual/html_node/A-Complete-C_002b_002b-Example.html

enum class Mode
{
    LEX,
    PARSE
};

static const map<string, Mode> flag_to_mode = {
    {"-l", Mode::LEX},
    {"-p", Mode::PARSE},
};

int main(int argc, char const *argv[])
{
    Mode mode;
    string source_file;

    if (argc == 2)
    {
        mode = Mode::PARSE;
        source_file = argv[1];
    }
    else if (argc == 3)
    {
        if (flag_to_mode.count(argv[1]) == 0)
        {
            cerr << "Invalid mode: " << argv[1] << endl;
            return -1;
        }
        mode = flag_to_mode.at(argv[1]);
        source_file = argv[2];
    }
    else
    {
        cerr << "Usage: " << argv[0] << " [-l|-p] <source_file>" << endl;
        return -1;
    }

    VSOP::Driver driver = VSOP::Driver(source_file);

    int res;
    switch (mode)
    {
    case Mode::LEX:
        res = driver.lex();

        driver.print_tokens();

        return res;

    case Mode::PARSE:
        res = driver.parse();
        if (res == 0)
        {      
            cout << "Finished parsing" << endl;
            cout << driver.programAst->serialize() << endl;
        }

        return res;
    }

    return 0;
}