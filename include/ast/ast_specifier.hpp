#ifndef ast_specifier_hpp
#define ast_specifier_hpp

#include <string>
#include <iostream>

class ASTSpecifier
    : public ASTNode
{
private:
    std::string basicSpecifier;
    ASTNode* left;
    ASTNode* right;
public:
    ASTSpecifier(std::string _basicSpecifier) : basicSpecifier(_basicSpecifier) {}
    ASTSpecifier(ASTNode* _left, ASTNode* _right) : left(_left), right(_right) {}
    virtual ~ASTSpecifier() {
        if (left != NULL) delete left;
        if (right != NULL) delete right;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        if (basicSpecifier != "") {
            dst<<basicSpecifier;
        } else if (left != NULL && right != NULL) {
            left->printPy(dst, indentLevel, GlobalIdentifiers);
            dst<<" ";
            right->printPy(dst, indentLevel, GlobalIdentifiers);
        }
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {}
};

#endif