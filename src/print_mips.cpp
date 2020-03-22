#include "ast.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    const ASTNode* ast;
    std::ostream& os = std::cout;

    ast=parseAST();
    Context context;
    ast->printMIPS(os, context);

    return 0;
}
 