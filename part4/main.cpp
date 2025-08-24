/**
 * @brief Main program for VSOP COMPILER. Options -l : lex source code, -p : parse source code, -c : semantic analysis, -i : generate LLVM IR, -e : extended VSOP
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>

#include "driver.hpp"

using namespace std;

// Adapted from https://www.gnu.org/software/bison/manual/html_node/A-Complete-C_002b_002b-Example.html

enum class Mode
{
    LEX,
    PARSE,
    SEMANTIC,
    CODE_GEN
};

static const map<string, Mode> flag_to_mode = {
    {"-l", Mode::LEX},
    {"-p", Mode::PARSE},
    {"-c", Mode::SEMANTIC},
    {"-i", Mode::CODE_GEN},
};

int main(int argc, char const *argv[])
{
    Mode mode;
    string source_file;
    bool extended_vsop = false;

    if (argc == 2)
    {
        mode = Mode::CODE_GEN; // Default: code generation
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
        cerr << "Usage: " << argv[0] << " [-l|-p|-c|-i] <source_file>" << endl;
        return -1;
    }

    VSOP::Driver driver = VSOP::Driver(source_file, extended_vsop);

    int res;
    switch (mode)
    {
    case Mode::LEX:
        res = driver.lex();
        driver.print_tokens();
        return res;

    case Mode::PARSE:
        res = driver.parseWithoutSemantic();
        if (res == 0)
        {
            cout << driver.programAst->getString() << endl;
        }
        return res;

    case Mode::SEMANTIC:
        res = driver.parse();
        if (res == 0)
        {
            if (driver.semanticAnalyzer)
            {
                cout << driver.semanticAnalyzer->getAnnotatedString() << endl;
            }
            else
            {
                cout << driver.programAst->getString() << endl;
            }
        }
        return res;

    case Mode::CODE_GEN:
        res = driver.parse();
        if (res == 0)
        {
            if (driver.semanticAnalyzer)
            {
                // Generate LLVM IR and output to stdout
                driver.generateLLVMIR();
            }
            else
            {
                cerr << "Semantic analysis failed, cannot generate code" << endl;
                return -1;
            }
        }
        return res;
    }
    return 0;
}
