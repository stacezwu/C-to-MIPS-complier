#include "ast.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    const ASTNode* ast;
    std::ostream* outputStream = &std::cout;
    std::string outputMode = "translate";
    
    std::vector<std::string> GlobalIdentifiers; // for python
    Context context; // for MIPS
    int indentLevel = 0;
    
    // TODO: parse command line arguments properly + make sure the boilerplate code for calling the main function is also printed when using stdout instead of a file output
    if (argc < 2) {
        ast=parseAST();
    } else if (argc > 5) {
        std::cerr << "Invalid number of arguments." << std::endl;
        exit(-1);// TODO (Horace): figure out what return code I should actually use
    } else {
        ast=parseAST(argv[2]);
        
        if (argv[1] == std::string("-S")) outputMode = "compile";
        
        std::ofstream* outputFile = new std::ofstream(argv[4]);
        if (outputFile->is_open()) {
            outputStream = outputFile;
        } else {
            std::cerr << "Cannot open output file...printing to stdout." << std::endl;
        }
    }
    
    if (outputMode == std::string("translate")) {
        // std::cout<<"translating"<<std::endl;
        ast->printPy(*outputStream, indentLevel, GlobalIdentifiers);
    }
    else ast->printMIPS(*outputStream, context);
    
    if (argc > 4 && argv[4]) delete outputStream;

    return 0;
}
