#ifndef ast_specifier_hpp
#define ast_specifier_hpp

#include <string>
#include <iostream>

class ASTSpecifierList
    : public Expression
{
public:
    std::set<std::string> specifiers;
    ASTSpecifierList(std::string _basicSpecifier) {
        specifiers.insert(_basicSpecifier);
    }
    virtual ~ASTSpecifierList() {
    }
    
    virtual ASTSpecifierList* insert(ASTSpecifierList* _basicSpecifier) {
        for (auto _specifier : _basicSpecifier->specifiers) {
            specifiers.insert(_specifier);
        }
        return this;
    }
    
    // virtual int getSizeOf() {
    //     if (specifiers.count("int") > 0) {
    //         return 4;
    //     } else {
    //         return -1; // TODO
    //     }
    // }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        // do nothing
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {}
};

#endif