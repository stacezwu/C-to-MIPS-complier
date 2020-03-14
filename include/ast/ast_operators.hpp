#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>

class Operator : public Expression {
protected:
    ExpressionPtr left;
    ExpressionPtr right;
    Operator(ExpressionPtr _left, ExpressionPtr _right) : left(_left), right(_right) {}
public:
    virtual ~Operator() {
        if (left != NULL) delete left;
        if (right != NULL) delete right;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr getLeft() const { return left; }
    ExpressionPtr getRight() const { return right; }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<"( ";
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
        dst<<" )";
    }
};

class AddOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        double vl=getLeft()->evaluate(bindings);
        double vr=getRight()->evaluate(bindings);
        return vl+vr;
    }
};

class SubOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        double vl=getLeft()->evaluate(bindings);
        double vr=getRight()->evaluate(bindings);
        return vl-vr;
    }
};


class MulOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        double vl=getLeft()->evaluate(bindings);
        double vr=getRight()->evaluate(bindings);
        return vl*vr;
    }
};

class DivOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        double vl=getLeft()->evaluate(bindings);
        double vr=getRight()->evaluate(bindings);
        return vl/vr;
    }
};

class ModOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "%"; }
public:
    ModOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
};

class LessThanOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "<"; }
public:
    LessThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
};

class GreaterThanOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return ">"; }
public:
    GreaterThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
};

class LessThanEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "<="; }
public:
    LessThanEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
};

class GreaterThanEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return ">="; }
public:
    GreaterThanEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
};

class EqEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "=="; }
public:
    EqEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

};

class NotEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "!="; }
public:
    NotEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

};

class LogicalNotOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "!"; }
public:
    LogicalNotOperator(ExpressionPtr _right)
        : Operator(NULL, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<" "<<"not"<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};

class LogicalOrOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "||"; }
public:
    LogicalOrOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<"or"<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};


class LogicalAndOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "&&"; }
public:
    LogicalAndOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<"and"<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};



class EqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "="; }
public:
    EqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};

class PlusEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "+="; }
public:
    PlusEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};

class MinusEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "-="; }
public:
    MinusEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};

class TimesEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "*="; }
public:
    TimesEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};

class DivideEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "/="; }
public:
    DivideEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};

class ModEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "%="; }
public:
    ModEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
};

class FunctionCall : public Expression {
protected:
    std::string* functionName;
    ExpressionPtr expr;
public:
    FunctionCall(std::string* _functionName, ExpressionPtr _expr) : functionName(_functionName), expr(_expr) {}
    virtual ~FunctionCall() {
        delete functionName;
        if (expr != NULL) delete expr;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<*functionName<<"(";
        if (expr != NULL) expr->printPy(dst, -1, GlobalIdentifiers);
        dst<<")";
    }
};


#endif


/*
TODO operators (Stacey):
OP_LOGICAL_NOT OP_LOGICAL_OR OP_LOGICAL_AND
OP_EQ_EQ OP_NEQ OP_LT OP_GT OP_LTE OP_GTE

- Jump statements
- Selection/iteration statements

TODO (Horace):
- assignment operators

- Identifiers
- Functions + function call operator


Changes made
- created ASTNode class - all Expressions, Statements, Functions, etc. inherit from ASTNode now
- basic function declaration
- added destructors to classes that should have a destructor

*/