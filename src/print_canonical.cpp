#include "ast.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    const ASTNode* ast;
    std::ostream& os = std::cout;
    
    std::vector<std::string> GlobalIdentifiers;
    int indentLevel = 0;
    
    // TODO: parse command line arguments properly + make sure the boilerplate code for calling the main function is also printed when using stdout instead of a file output
    // + add a "return 0" to main if no return statement is specified
    if (argc < 2) {
        ast=parseAST();
        ast->printPy(os, indentLevel, GlobalIdentifiers);
    } else if (argc == 5) {
        ast=parseAST(argv[2]);
        
        std::ofstream outputFile(argv[4]);
        if (outputFile.is_open()) {
            ast->printPy(outputFile, indentLevel, GlobalIdentifiers);
            outputFile<<std::endl;
            outputFile<<"if __name__ == \"__main__\":"<<std::endl;
            outputFile<<"   import sys"<<std::endl;
            outputFile<<"   ret=main()"<<std::endl;
            outputFile<<"   sys.exit(ret)"<<std::endl;
            
            // os = outputFile;
        } else {
            std::cerr << "Cannot open output file...printing to stdout." << std::endl;
        }
    } else {
        std::cerr << "Error in number of arguments." << std::endl;
        exit(-1);// TODO (Horace): figure out what return code I should actually use
    }
    
    // ast->printPy(os, indentLevel, GlobalIdentifiers);
    std::cout<<std::endl;

    return 0;
}
