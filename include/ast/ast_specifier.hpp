#ifndef ast_specifier_hpp
#define ast_specifier_hpp

#include <string>
#include <iostream>

class ASTSpecifierList
    : public Expression
{
protected:
    std::string mode = "default"; // "default" for basic data types e.g. int, long int, etc. and "user-defined" for enum, struct, etc.
    ASTNode* userDefinedSpecifier; // for enum specifiers, etc.
public:
    std::set<std::string> specifiers;
    ASTSpecifierList(std::string _basicSpecifier) {
        specifiers.insert(_basicSpecifier);
    }
    ASTSpecifierList(ASTNode* _userDefinedSpecifier) : userDefinedSpecifier(_userDefinedSpecifier) {
        mode = "user-defined";
        specifiers.insert("enum");
    }
    virtual ~ASTSpecifierList() {
        if (mode == "user-defined" && userDefinedSpecifier != NULL) delete userDefinedSpecifier;
    }
    
    virtual ASTSpecifierList* insert(ASTSpecifierList* _basicSpecifier) {
        for (auto _specifier : _basicSpecifier->specifiers) {
            specifiers.insert(_specifier);
        }
        return this;
    }
    
    virtual int getSizeOf(Context& context) const {
        if (specifiers.count("pointer") > 0) return 4;
        else if (specifiers.count("long") > 0 && specifiers.count("double") > 0) return 8;
        else if (specifiers.count("long") > 0) return 4;
        else if (specifiers.count("short") > 0) return 2;
        else if (specifiers.count("char") > 0) return 1;
        else if (specifiers.count("float") > 0) return 4;
        else if (specifiers.count("double") > 0) return 8;
        else if (specifiers.count("int") > 0) return 4;
        else {
            return 4;
        }
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        // do nothing
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (mode == "user-defined" && userDefinedSpecifier != NULL) userDefinedSpecifier->printMIPS(dst, context);
    }
};

#endif