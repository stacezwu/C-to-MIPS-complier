#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include <string>
#include <iostream>

// class Initializer : public ASTNode {
    
// }

// std::vector<Declaration*> GlobalVariables;
// void addtoGlobalVariables(Declaration* _declaration){
//     GlobalVariables.push_back(_declaration);
// }


class Declaration : public ASTNode {
private:
    // ASTSpecifier* specifiers;
    ASTNode* specifiers;
    std::string* identifier;
    ASTNode* initializer;
    

public:
    
    Declaration(ASTNode* _specifiers, std::string* _identifier, ASTNode* _initializer) : specifiers(_specifiers), identifier(_identifier), initializer(_initializer) {}
    virtual ~Declaration() {
        delete specifiers;
        delete identifier;
        delete initializer;
    };
    
    std::string getDeclarationIdentifier() const{
        return *identifier;
    }
    
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        if (indentLevel == 0){
            GlobalIdentifiers.push_back(getDeclarationIdentifier());
        }
        dst<<getIndent(indentLevel);
        // specifiers->printPy(dst);
        dst<<*identifier;
        if (initializer == NULL) dst<<" = 0"; // TODO: change later
        else {
            dst<<"=";
            initializer->printPy(dst, indentLevel, GlobalIdentifiers);
        }
        dst<<std::endl;
    }
};

// class DeclarationList: public Declaration{
// protected:
    
// public: 

// };

#endif
