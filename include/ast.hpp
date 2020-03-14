#ifndef ast_hpp
#define ast_hpp

#include <iostream>
#include <string>
#include <vector>



class ASTNode {
protected:
    static std::string getIndent(int indentLevel) {
        std::string indent = "";
        for (int i = 0; i < indentLevel; i++) indent += "   ";
        return indent;
    }

public:
    virtual ~ASTNode() {}
    
    //std::vector<std::string*> GlobalIdentifiers;
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const = 0;
};

class TranslationUnit : public ASTNode {
protected:
    std::vector<ASTNode*> externalDeclarations;
    
public:
    TranslationUnit(ASTNode* _externalDeclaration) {
        externalDeclarations.push_back(_externalDeclaration);
    }
    virtual ~TranslationUnit() {
        for (auto _externalDeclaration : externalDeclarations) {
            delete _externalDeclaration;
        }
        externalDeclarations.clear();
    }
    
    TranslationUnit* insertExternalDeclaration(ASTNode* _externalDeclaration) {
        externalDeclarations.push_back(_externalDeclaration);
        return this;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        for (auto _externalDeclaration : externalDeclarations) {
            _externalDeclaration->printPy(dst, indentLevel, GlobalIdentifiers);
        }
    }
};

#include "ast/ast_expression.hpp"
#include "ast/ast_primary_expression.hpp"
#include "ast/ast_statement.hpp"
#include "ast/ast_operators.hpp"
// #include "ast/ast_unary.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_specifier.hpp"
#include "ast/ast_declaration.hpp"

extern const ASTNode* parseAST();

#endif
