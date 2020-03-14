#ifndef ast_function_hpp
#define ast_function_hpp

#include <string>
#include <iostream>

// basic function definition with no parameters and other features
class FunctionDefinition : public ASTNode {
protected:
    ASTNode* typeSpecifier;
    std::string* functionName;
    Statement* functionBody;
public:
    FunctionDefinition(ASTNode* _typeSpecifier, std::string* _functionName, Statement* _functionBody) : typeSpecifier(_typeSpecifier), functionName(_functionName), functionBody(_functionBody) {}
    virtual ~FunctionDefinition() {
        delete typeSpecifier;
        delete functionName;
        delete functionBody;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst << "def " << *functionName << "():" << std::endl;
        
        // void printGlobal(std::ostream &dst){
            for (int i = 0; i < GlobalIdentifiers.size(); i++){
                dst<<"global ";
                dst<<GlobalIdentifiers[i]<<std::endl;
            }
        // }
        functionBody->printPy(dst, indentLevel+1, GlobalIdentifiers);
    }
};



#endif
