#include "ast.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    const ASTNode* ast;
    std::ostream& os = std::cout;

    ast=parseAST();
    std::vector<std::string> GlobalIdentifiers;
    int indentLevel = 0;
    ast->printPy(os, indentLevel, GlobalIdentifiers);

    return 0;
}
 