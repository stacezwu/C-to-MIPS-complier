#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

class Expression;

typedef const Expression* ExpressionPtr;

class Expression : public ASTNode {
public:
    virtual ~Expression() {};
    
    // virtual std::set<std::string> getTypes(Context& context) const = 0;
    // TODO: for pointer arithmetic and other purposes

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const = 0;
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {}

    //! Evaluate the tree using the given mapping of variables to numbers
    virtual double evaluate() const
    { throw std::runtime_error("Not implemented."); }
};

#endif
