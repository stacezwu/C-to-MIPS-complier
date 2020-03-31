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

    virtual double evaluate() const override
    {
        double vl=getLeft()->evaluate();
        double vr=getRight()->evaluate();
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

    virtual double evaluate() const override
    {
        double vl=getLeft()->evaluate();
        double vr=getRight()->evaluate();
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

    virtual double evaluate() const override
    {
        double vl=getLeft()->evaluate();
        double vr=getRight()->evaluate();
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

    virtual double evaluate() const override
    {
        double vl=getLeft()->evaluate();
        double vr=getRight()->evaluate();
        return vl/vr;
    }

    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"divu $2, $3"<<std::endl;
        dst<<"mflo $"<<destReg<<std::endl; 
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

    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"divu $2, $3"<<std::endl;
        dst<<"mfhi $"<<destReg<<std::endl; 
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class LessThanOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "<"; }
public:
    LessThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"slt $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class GreaterThanOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return ">"; }
public:
    GreaterThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"slt $"<<destReg<<", $3, $2"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);    
    }
};

class LessThanEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "<="; }
public:
    LessThanEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"slt $"<<destReg<<", $3, $2"<<std::endl;
        dst<<"xori $"<<destReg<<", $"<<destReg<<", 1"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class GreaterThanEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return ">="; }
public:
    GreaterThanEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"slt $"<<destReg<<", $2, $3"<<std::endl;
        dst<<"xori $"<<destReg<<", $"<<destReg<<", 1"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
};

class EqEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "=="; }
public:
    EqEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"sub $"<<destReg<<", $2, $3"<<std::endl;
        dst<<"sltiu $"<<destReg<<", $"<<destReg<<", 1"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }

};

class NotEqOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "!="; }
public:
    NotEqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"sub $"<<destReg<<", $2, $3"<<std::endl;
        //set destReg = 1 if 0<$2
        dst<<"sltu $"<<destReg<<", $0, $"<<destReg<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        // if (destReg == 2) context.pushToStack(dst, 3);
        // if (destReg == 3) context.pushToStack(dst, 2);
        //left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, destReg); 
        dst<<"sltiu $"<<destReg<<", $"<<destReg<<", 1"<<std::endl;
        // if (destReg == 2) context.popFromStack(dst, 3);
        // if (destReg == 3) context.popFromStack(dst, 2);      
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

    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string pass = context.makeLabel("pass");
        std::string fail = context.makeLabel("fail");
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"bne $2, $0, "<<pass<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<"bne $3, $0, "<<pass<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<"move $"<<destReg<<", $0"<<std::endl;
        dst<<"b "<<fail<<std::endl;
        dst<<pass<<":"<<std::endl;
        dst<<"li $"<<destReg<<", 1"<<std::endl;
        dst<<fail<<":"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string pass = context.makeLabel("pass");
        std::string fail = context.makeLabel("fail");
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"beq $2, $0, "<<fail<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<"beq $3, $0, "<<fail<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<"li $"<<destReg<<", 1"<<std::endl;
        dst<<"j "<<pass<<std::endl;
        dst<<fail<<":"<<std::endl;
        dst<<"li $"<<destReg<<", 0"<<std::endl;
        dst<<pass<<":"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
};



class EqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "="; }
public:
    EqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        right->printMIPS(dst, context, destReg);
        left->writeValue(dst, context, destReg);
    }
};

class PlusEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "+="; }
public:
    PlusEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"addu $"<<destReg<<", $2, $3"<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class MinusEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "-="; }
public:
    MinusEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"subu $"<<destReg<<", $2, $3"<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class TimesEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "*="; }
public:
    TimesEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }

    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"mult $2, $3"<<std::endl;
        dst<<"mflo $"<<destReg<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class DivideEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "/="; }
public:
    DivideEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"divu $2, $3"<<std::endl;
        dst<<"mflo $"<<destReg<<std::endl; 
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class ModEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "%="; }
public:
    ModEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        left->printPy(dst, -1, GlobalIdentifiers);
        dst<<" "<<getOpcode()<<" ";
        right->printPy(dst, -1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"divu $2, $3"<<std::endl;
        dst<<"mfhi $"<<destReg<<std::endl; 
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class AndEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "&="; }
public:
    AndEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"and $"<<destReg<<", $2, $3"<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class OrEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "|="; }
public:
    OrEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"or $"<<destReg<<", $2, $3"<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class XorEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "^="; }
public:
    XorEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"xor $"<<destReg<<", $2, $3"<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class LeftshiftEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "<<="; }
public:
    LeftshiftEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"sllv $"<<destReg<<", $2, $3"<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class RightshiftEqOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return ">>="; }
public:
    RightshiftEqOperator(ModifiableLValue* _left, ExpressionPtr _right)
        : Operator(_left, _right), left(_left)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3);
        dst<<"srav $"<<destReg<<", $2, $3"<<std::endl;
        left->writeValue(dst, context, destReg);
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);
    }
};

class BitwiseAndOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "&"; }
public:
    BitwiseAndOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"and $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
};


class BitwiseOrOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "|"; }
public:
    BitwiseOrOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"or $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
};

class BitwiseNotOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "~"; }
public:
    BitwiseNotOperator(ExpressionPtr _right)
        : Operator(NULL, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        right->printMIPS(dst, context, destReg); 
        dst<<"nor $"<<destReg<<", $0, $"<<destReg<<std::endl;
    }
};

class BitwiseXorOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    BitwiseXorOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"xor $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
};

class LeftshiftOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "<<"; }
public:
    LeftshiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"sllv $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
};

class RightshiftOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return ">>"; }
public:
    RightshiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (destReg == 2) context.pushToStack(dst, 3);
        if (destReg == 3) context.pushToStack(dst, 2);
        left->printMIPS(dst, context, 2);
        right->printMIPS(dst, context, 3); 
        dst<<"srav $"<<destReg<<", $2, $3"<<std::endl;
        if (destReg == 2) context.popFromStack(dst, 3);
        if (destReg == 3) context.popFromStack(dst, 2);      
    }
};

class UnaryPlusOperator : public Operator {
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    UnaryPlusOperator(ExpressionPtr _right)
        : Operator(NULL, _right)
    {}
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        // left->printPy(dst, -1, GlobalIdentifiers);
        dst<<getOpcode();
        right->printPy(dst, -1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        right->printMIPS(dst, context, destReg);
    }
};

class UnaryMinusOperator : public Operator {
protected:

    virtual const char *getOpcode() const override
    { return "-"; }
public:
    UnaryMinusOperator(ExpressionPtr _right)
        : Operator(NULL, _right)
    {}
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        // left->printPy(dst, -1, GlobalIdentifiers);
        dst<<getOpcode();
        right->printPy(dst, -1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        right->printMIPS(dst, context, destReg);
        dst<<"subu $"<<destReg<<", $0, $"<<destReg<<std::endl;
    }
};

class PostfixIncrementOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "++"; }
public:
    PostfixIncrementOperator(ModifiableLValue* _left)
        : Operator(_left, NULL), left(_left)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        context.pushToStack(dst, 3);
        left->printMIPS(dst, context, destReg);
        dst<<"addiu $3, $"<<destReg<<", 1"<<std::endl;
        left->writeValue(dst, context, 3);
        context.popFromStack(dst, 3);
    }
};

class PostfixDecrementOperator : public Operator {
protected:
    ModifiableLValue* left;
    virtual const char *getOpcode() const override
    { return "--"; }
public:
    PostfixDecrementOperator(ModifiableLValue* _left)
        : Operator(_left, NULL), left(_left)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        context.pushToStack(dst, 3);
        left->printMIPS(dst, context, destReg);
        dst<<"addiu $3, $"<<destReg<<", -1"<<std::endl;
        left->writeValue(dst, context, 3);
        context.popFromStack(dst, 3);
    }
};

class PrefixIncrementOperator : public Operator {
protected:
    ModifiableLValue* right;
    virtual const char *getOpcode() const override
    { return "++"; }
public:
    PrefixIncrementOperator(ModifiableLValue* _right)
        : Operator(_right, NULL), right(_right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        right->printMIPS(dst, context, destReg);
        dst<<"addiu $"<<destReg<<", $"<<destReg<<", 1"<<std::endl;
        right->writeValue(dst, context, destReg);
    }
};

class PrefixDecrementOperator : public Operator {
protected:
    ModifiableLValue* right;
    virtual const char *getOpcode() const override
    { return "--"; }
public:
    PrefixDecrementOperator(ModifiableLValue* _right)
        : Operator(_right, NULL), right(_right)
    {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        right->printMIPS(dst, context, destReg);
        dst<<"addiu $"<<destReg<<", $"<<destReg<<", -1"<<std::endl;
        right->writeValue(dst, context, destReg);
    }
};

class AddressOfOperator : public Expression {
    ModifiableLValue* right;
public:
    AddressOfOperator(ModifiableLValue* _right) : right(_right) {}
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        right->printAddress(dst, context, destReg);
        // TODO: implement address of function (i.e. &func)
    }
};

class ArgumentList : public ASTNode {
protected:
    std::vector<ExpressionPtr> arguments;
    std::string functionName;
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
    
    void setFunctionName(std::string _functionName) { functionName = _functionName; }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        for (auto argument : arguments) {
            argument->printPy(dst, indentLevel, GlobalIdentifiers);
            dst<<", ";
        }
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        for (unsigned int i = 0; i < arguments.size(); i++) {
            if (i < 4) {
                arguments[i]->printMIPS(dst, context, 4+i); // place first 4 arguments into argument registers ($4-$7)
            } else {
                arguments[i]->printMIPS(dst, context, 2);
                dst<<"sw $2, "<<i*4<<"($fp)"<<std::endl;
                // (Horace) Code below no longer used but I'm keeping it here for reference
                // std::string parameterName = Context::allFunctions.at(functionName)->functionContext->parameters[i];
                // int offset = Context::allFunctions.at(functionName)->functionContext->localVarOffsets.at(parameterName);
                // offset -= Context::allFunctions.at(functionName)->functionContext->frameSize;
                // dst<<"sw $2, "<<offset<<"($fp)"<<std::endl;
            }
        }
    }
};

class FunctionCall : public Expression {
protected:
    std::string* functionName;
    ArgumentList* arguments;
public:
    FunctionCall(std::string* _functionName, ArgumentList* _arguments) : functionName(_functionName), arguments(_arguments) {
        if (arguments != NULL) {
            arguments->setFunctionName(*functionName);
        }
    }
    virtual ~FunctionCall() {
        delete functionName;
        if (arguments != NULL) delete arguments;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<*functionName<<"(";
        if (arguments != NULL) arguments->printPy(dst, -1, GlobalIdentifiers);
        dst<<")";
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        // if (destReg == 2) do nothing
        if (destReg != 2) context.pushToStack(dst, 2);
        if (arguments != NULL) arguments->printMIPS(dst, context, 2);
        dst<<"jal "<<*functionName<<std::endl; // the function being called is expected to write its return value to $2
        dst<<"nop"<<std::endl;
        if (destReg != 2) {
            dst<<"move $"<<destReg<<", $2"<<std::endl;
            context.popFromStack(dst, 2);
        }
    }
};

class SizeOfOperator : public Expression {
protected:
    Expression* expr;
public:
    SizeOfOperator(Expression* _expr) : expr(_expr) {
    }
    virtual ~SizeOfOperator() {
        delete expr;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        dst<<"li $"<<destReg<<", "<<expr->getSizeOf(context)<<std::endl;
    }
};

#endif
