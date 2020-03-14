#ifndef ast_primary_expression_hpp
#define ast_primary_expression_hpp

#include <string>
#include <iostream>

class Variable
    : public Expression
{
private:
    std::string* id;
public:
    Variable(std::string* _id) : id(_id) {}
    virtual ~Variable() {
        delete id;
    }

    const std::string getId() const
    { return *id; }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override
    {
        dst<<*id;
    }

    // virtual double evaluate(
    //     const std::map<std::string,double> &bindings
    // ) const override
    // {
    //     // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
    //     // If the binding does not exist, this will throw an error
    //     return bindings.at(id);
    // }
};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value) : value(_value) {}
    virtual ~Number() {}

    double getValue() const
    { return value; }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override
    {
        dst<<value;
    }

    // virtual double evaluate(
    //     const std::map<std::string,double> &bindings
    // ) const override
    // {
    //     // TODO-A : Run bin/eval_expr with a numeric expression to make sure you understand how this works.
    //     return value;
    // }
};

class StringLiteral
    : public Expression
{
private:
    std::string* value;
public:
    StringLiteral(std::string* _value) : value(_value) {}
    virtual ~StringLiteral() {
        delete value;
    }

    std::string getValue() const
    { return *value; }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override
    {
        dst<<*value;
    }

    // virtual double evaluate(
    //     const std::map<std::string,double> &bindings
    // ) const override
    // {
    //     // TODO: fix later
    //     return 0.4321;
    // }
};


#endif
