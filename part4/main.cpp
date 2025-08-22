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
     CODE_GEN,
     NATIVE_EXEC
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
         mode = Mode::NATIVE_EXEC; // Default: generate native executable
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
     else if (argc == 4)
     {
         if (string(argv[1]) == "-e" && string(argv[2]) == "-i")
         {
             extended_vsop = true;
             mode = Mode::CODE_GEN;
             source_file = argv[3];
         }
         else if (string(argv[1]) == "-e")
         {
             extended_vsop = true;
             mode = Mode::NATIVE_EXEC;
             source_file = argv[2];
         }
         else
         {
             cerr << "Usage: " << argv[0] << " [-l|-p|-c|-i] <source_file>" << endl;
             cerr << "       " << argv[0] << " -e <source_file>" << endl;
             cerr << "       " << argv[0] << " -e -i <source_file>" << endl;
             return -1;
         }
     }
     else
     {
         cerr << "Usage: " << argv[0] << " [-l|-p|-c|-i] <source_file>" << endl;
         cerr << "       " << argv[0] << " -e <source_file>" << endl;
         cerr << "       " << argv[0] << " -e -i <source_file>" << endl;
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
             if (driver.semanticAnalyzer) {
                 cout << driver.semanticAnalyzer->getAnnotatedString() << endl;
             } else {
                 cout << driver.programAst->getString() << endl;
             }
         }
         return res;
 
     case Mode::CODE_GEN:
         res = driver.parse();
         if (res == 0)
         {
             if (driver.semanticAnalyzer) {
                 // Generate LLVM IR and output to stdout
                 driver.generateLLVMIR();
             } else {
                 cerr << "Semantic analysis failed, cannot generate code" << endl;
                 return -1;
             }
         }
         return res;
 
     case Mode::NATIVE_EXEC:
         res = driver.parse();
         if (res == 0)
         {
             if (driver.semanticAnalyzer) {
                 // Generate native executable
                 string output_name = source_file;
                 if (output_name.substr(output_name.length() - 5) == ".vsop") {
                     output_name = output_name.substr(0, output_name.length() - 5);
                 }
                 
                 if (driver.generateNativeExecutable(output_name)) {
                     cout << "Successfully generated executable: " << output_name << endl;
                 } else {
                     cerr << "Failed to generate native executable" << endl;
                     return -1;
                 }
             } else {
                 cerr << "Semantic analysis failed, cannot generate code" << endl;
                 return -1;
             }
         }
         return res;
     }
 
     return 0;
 }