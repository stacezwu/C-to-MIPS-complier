#include "ast.hpp"

int main()
{
    const ASTNode* ast=parseAST();
    
    std::vector<std::string> GlobalIdentifiers;
    int indentLevel = 0;
    
    ast->printPy(std::cout, indentLevel, GlobalIdentifiers);
    std::cout<<std::endl;

    return 0;
}
