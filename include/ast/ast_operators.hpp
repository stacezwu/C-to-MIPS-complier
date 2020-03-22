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
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {}
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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"addu $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"subu $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"mult $2, $3"<<std::endl;
        dst<<"mflo $"<<destReg<<std::endl; 
        // destReg store LSB 16 of answer
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
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

    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"mult $2, $3"<<std::endl;
        dst<<"mflo $"<<destReg<<std::endl; 
        // destReg store LSB 16 of answer
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
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
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        int offset; // = lookup offset of variable of LHS
        right->printMIPS(dst, context, destReg);
        dst<<"sw $"<<destReg<<", $"<<offset<<"($fp)"<<std::endl;
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


class ArgumentList : public ASTNode {
protected:
    std::vector<ExpressionPtr> arguments;
public:
    ArgumentList(ExpressionPtr _argument) {
        arguments.push_back(_argument);
    }
    
    virtual ~ArgumentList() {
        for (auto argument : arguments) {
            delete argument;
        }
        arguments.clear();
    }
    
    ArgumentList* addArgument(ExpressionPtr _argument) {
        arguments.push_back(_argument);
        return this;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        for (auto argument : arguments) {
            argument->printPy(dst, indentLevel, GlobalIdentifiers);
            dst<<", ";
        }
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {}
};


class FunctionCall : public Expression {
protected:
    std::string* functionName;
    ArgumentList* arguments;
public:
    FunctionCall(std::string* _functionName, ArgumentList* _arguments) : functionName(_functionName), arguments(_arguments) {}
    virtual ~FunctionCall() {
        delete functionName;
        if (arguments != NULL) delete arguments;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<*functionName<<"(";
        if (arguments != NULL) arguments->printPy(dst, -1, GlobalIdentifiers);
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