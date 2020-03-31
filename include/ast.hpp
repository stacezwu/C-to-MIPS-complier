#ifndef ast_hpp
#define ast_hpp


#include <iostream>
#include <string>
#include <vector>
#include <set>

class Context;

class ASTNode {
protected:
    static std::string getIndent(int indentLevel) {
        std::string indent = "";
        for (int i = 0; i < indentLevel; i++) indent += "   ";
        return indent;
    }

    void printGlobal(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const{
        for (unsigned int i = 0; i < GlobalIdentifiers.size(); i++){
            dst<<getIndent(indentLevel);
            dst<<"global ";
            dst<<GlobalIdentifiers[i]<<std::endl;
        }
    }

public:
    virtual ~ASTNode() {};
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const = 0;
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const = 0;
};


class ASTNodeList : public ASTNode {
public:
    virtual ~ASTNodeList() {};
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const = 0;
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const = 0;
    
    virtual ASTNodeList* insert(ASTNode* _node) = 0;
};


class TranslationUnit : public ASTNodeList {
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
    
    TranslationUnit* insert(ASTNode* _node) {
        externalDeclarations.push_back(_node);
        return this;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        for (auto _externalDeclaration : externalDeclarations) {
            _externalDeclaration->printPy(dst, indentLevel, GlobalIdentifiers);
        }
        
        dst<<std::endl;
        dst<<"if __name__ == \"__main__\":"<<std::endl;
        dst<<"   import sys"<<std::endl;
        dst<<"   ret=main()"<<std::endl;
        dst<<"   sys.exit(ret)"<<std::endl;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        for (auto _externalDeclaration : externalDeclarations) {
            _externalDeclaration->printMIPS(dst, context);
        }
    }
};

#include "Context.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_primary_&_lvalue_expression.hpp"
#include "ast/ast_statement.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_specifier.hpp"
#include "ast/ast_declaration.hpp"

extern const ASTNode* parseAST();
extern const ASTNode* parseAST(char* inFile);

#endif
