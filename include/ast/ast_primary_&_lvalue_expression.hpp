#ifndef ast_primary_and_lvalue_expression_hpp
#define ast_primary_and_lvalue_expression_hpp

#include <string>
#include <iostream>
#include <cstdint>
#include <math.h>

class ModifiableLValue : public Expression {
public:
    virtual ~ModifiableLValue() {}
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const = 0;
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const = 0;
    virtual void writeValue(std::ostream &dst, Context& context, int sourceReg) const = 0;
    virtual void printAddress(std::ostream &dst, Context& context, int destReg = 2) const = 0;
};

class Variable
    : public ModifiableLValue
{
private:
    std::string* identifier;
public:
    Variable(std::string* _identifier) : identifier(_identifier) {}
    virtual ~Variable() {
        delete identifier;
    }

    const std::string getIdentifier() const
    { return *identifier; }
    
    virtual int getSizeOf(Context& context) const {
        if (context.localVarOffsets.count(*identifier) != 0) {
            return context.localVarSizes.at(*identifier);
        } else {
            return context.globalVarSizes.at(*identifier);
        }
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override
    {
        dst<<*identifier;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        int typeSize = getSizeOf(context);
        std::string load_instr;
        if (typeSize == 1) load_instr = "lb";
        else if (typeSize == 2) load_instr = "lh";
        else load_instr = "lw";
        
        if (context.localVarOffsets.count(*identifier) != 0) {
            // local variable
            dst<<load_instr<<" $"<<destReg<<", "<<context.localVarOffsets.at(*identifier)<<"($fp)"<<std::endl;
            dst<<"nop"<<std::endl;
        } else {
            // global variable
            dst<<load_instr<<" $"<<destReg<<", "<<*identifier<<std::endl;
            dst<<"nop"<<std::endl;
        }
    }
    
    virtual void writeValue(std::ostream &dst, Context& context, int sourceReg) const {
        int typeSize = getSizeOf(context);
        std::string store_instr;
        if (typeSize == 1) store_instr = "sb";
        else if (typeSize == 2) store_instr = "sh";
        else store_instr = "sw"; // for now assume size is 4
            
        if (context.localVarOffsets.count(*identifier) != 0) {
            // local variable
            dst<<store_instr<<" $"<<sourceReg<<", "<<context.localVarOffsets.at(*identifier)<<"($fp)"<<std::endl;
            dst<<"nop"<<std::endl;
        } else {
            // global variable
            dst<<store_instr<<" $"<<sourceReg<<", "<<*identifier<<std::endl;
            dst<<"nop"<<std::endl;
        }
    }
    
    virtual void printAddress(std::ostream &dst, Context& context, int destReg = 2) const {
        if (context.localVarOffsets.count(*identifier) != 0) {
            // local variable
            dst<<"addiu $"<<destReg<<", $fp, "<<context.localVarOffsets.at(*identifier)<<std::endl;
        } else {
            // global variable
            dst<<"la $"<<destReg<<", "<<*identifier<<std::endl;
        }
    }
};

class ArrayElement : public ModifiableLValue {
protected:
    std::string* identifier;
    Expression* index;

public:
    ArrayElement(std::string* _identifier, Expression* _index) : identifier(_identifier), index(_index) {}
    virtual ~ArrayElement() {
        delete identifier;
        delete index;
    }
    
    virtual int getSizeOf(Context& context) const {
        if (context.localVarOffsets.count(*identifier) != 0) {
            return context.localArrayTypeSizes.at(*identifier);
        } else {
            return context.globalArrayTypeSizes.at(*identifier);
        }
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        int typeSize = getSizeOf(context);
        std::string load_instr;
        if (typeSize == 1) load_instr = "lb";
        else if (typeSize == 2) load_instr = "lh";
        else load_instr = "lw";
        
        dst<<"#debug: using "<<load_instr<<std::endl;
        
        // the address of the array element is given by ($fp + array_start_address + 4*index)
        index->printMIPS(dst, context, destReg);
        dst<<"sll $"<<destReg<<", $"<<destReg<<", "<<log2(typeSize)<<std::endl;

        if (context.localVarOffsets.count(*identifier) != 0) {
            // local variable
            
            if (context.localPointers.count(*identifier) > 0) {
                dst<<"lw $t0, "<<context.localVarOffsets.at(*identifier)<<"($fp)"<<std::endl;
                dst<<"addu $"<<destReg<<", $"<<destReg<<", $t0"<<std::endl;
                dst<<load_instr<<" $"<<destReg<<", 0($"<<destReg<<")"<<std::endl;
            } else {
                dst<<"addu $"<<destReg<<", $fp, $"<<destReg<<std::endl;
                dst<<load_instr<<" $"<<destReg<<", "<<context.localVarOffsets.at(*identifier)<<"($"<<destReg<<")"<<std::endl;
            }
            dst<<"nop"<<std::endl;
        } else {
            // global variable
            if (context.globalPointers.count(*identifier) > 0) {
                dst<<"la $t0, "<<*identifier<<std::endl;
                dst<<"lw $t0, 0($t0)"<<std::endl;
            } else {
                dst<<"la $t0, "<<*identifier<<std::endl;
            }
            dst<<"addu $t0, $t0, $"<<destReg<<std::endl;
            dst<<load_instr<<" $"<<destReg<<", 0($t0)"<<std::endl;
            dst<<"nop"<<std::endl;
        }
    }
    
    virtual void writeValue(std::ostream &dst, Context& context, int sourceReg) const {
        int typeSize = getSizeOf(context);
        std::string store_instr;
        if (typeSize == 1) store_instr = "sb";
        else if (typeSize == 2) store_instr = "sh";
        else store_instr = "sw"; // for now assume size is 4
        
        context.pushToStack(dst, 2); context.pushToStack(dst, 3);
        index->printMIPS(dst, context, 8); // write index to $t0
        context.popFromStack(dst, 3); context.popFromStack(dst, 2);
        dst<<"sll $8, $8, "<<log2(typeSize)<<std::endl;
        
        if (context.localVarOffsets.count(*identifier) != 0) {
            // local variable
            dst<<"addu $t0, $fp, $t0"<<std::endl;
            dst<<store_instr<<" $"<<sourceReg<<", "<<context.localVarOffsets.at(*identifier)<<"($t0)"<<std::endl;
            dst<<"nop"<<std::endl;
        } else {
            // // global variable
            dst<<"la $t1, "<<*identifier<<std::endl;
            dst<<"addu $t1, $t1, $t0"<<std::endl;
            dst<<store_instr<<" $"<<sourceReg<<", 0($t1)"<<std::endl;
            dst<<"nop"<<std::endl;
        }
    }
    
    virtual void printAddress(std::ostream &dst, Context& context, int destReg = 2) const {
        index->printMIPS(dst, context, destReg);
        dst<<"sll $"<<destReg<<", $"<<destReg<<", "<<log2(getSizeOf(context))<<std::endl;
        
        if (context.localVarOffsets.count(*identifier) != 0) {
            // local variable
            dst<<"addu $"<<destReg<<", $fp, $"<<destReg<<std::endl;
            dst<<"addiu $"<<destReg<<", $"<<destReg<<", "<<context.localVarOffsets.at(*identifier)<<std::endl;
        } else {
            // global variable
            dst<<"la $t0, "<<*identifier<<std::endl;
            dst<<"addu $"<<destReg<<", $"<<destReg<<", $t0"<<std::endl;
        }
    }
};

class DereferenceOperator : public ModifiableLValue {
protected:
    Expression* ptr_expr;
public:
    DereferenceOperator(Expression* _ptr_expr) : ptr_expr(_ptr_expr) {}
    virtual ~DereferenceOperator() {
        delete ptr_expr;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const { }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const {
        dst<<"#Dereference operator read"<<std::endl;
        ptr_expr->printMIPS(dst, context, destReg);
        dst<<"lw $"<<destReg<<", 0($"<<destReg<<")"<<std::endl;
        dst<<"nop"<<std::endl;
    }
    
    virtual void writeValue(std::ostream &dst, Context& context, int sourceReg) const {
        dst<<"#Dereference operator write"<<std::endl;
        context.pushToStack(dst, 2); context.pushToStack(dst, 3);
        ptr_expr->printMIPS(dst, context, 8); // write address to $t0
        context.popFromStack(dst, 3); context.popFromStack(dst, 2);
        
        if (context.inFunction == true) {
            dst<<"sw $"<<sourceReg<<", 0($t0)"<<std::endl;
            dst<<"nop"<<std::endl;
        } else {
            dst<<"sw $"<<sourceReg<<", 0($t0)"<<std::endl;
            dst<<"nop"<<std::endl;
        }
    }
    virtual void printAddress(std::ostream &dst, Context& context, int destReg = 2) const {}
};


class IntegerLiteral : public Expression {
private:
    int value;
public:
    IntegerLiteral(int _value) : value(_value) {}
    virtual ~IntegerLiteral() {}
    
    virtual int getSizeOf(Context& context) const {
        return 4; // assumes int
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<value;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        int val = static_cast<uint32_t>(value);
        dst<<"li $"<<destReg<<","<<val<<std::endl;
        // only support int 
    }

    virtual double evaluate() const override {
        return value;
    }
};

class DoubleLiteral : public Expression {
private:
    double value;
public:
    DoubleLiteral(double _value) : value(_value) {}
    virtual ~DoubleLiteral() {}
    
    virtual int getSizeOf(Context& context) const {
        return 4; // assumes int
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<value;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        int val = static_cast<uint32_t>(value);
        dst<<"li $"<<destReg<<","<<val<<std::endl;
        // only support int 
    }

    virtual double evaluate() const override {
        return value;
    }
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
    
    virtual int getSizeOf(Context& context) const {
        return value->length();
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override
    {
        dst<<*value;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        dst<<".data"<<std::endl;
        dst<<"string_lit_"<<(++context.stringLiteralCount)<<": .asciiz \""<<*value<<"\""<<std::endl;
        dst<<".text"<<std::endl;
        dst<<"la $"<<destReg<<", "<<"string_lit_"<<context.stringLiteralCount<<std::endl;
    }

    // virtual double evaluate() const override {}
};

class CharLiteral : public Expression {
private:
    int value;
public:
    CharLiteral(int _value) : value(_value) {}
    virtual ~CharLiteral() {}

    virtual int getSizeOf(Context& context) const {
        return 1;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override { }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        dst<<"li $"<<destReg<<","<<value<<std::endl;
    }

    virtual double evaluate() const override {
        return value;
    }
};

class ParenthesizedExpression : public Expression {
private:
    Expression* expr;
public:
    ParenthesizedExpression(Expression* _expr) : expr(_expr) {}
    virtual ~ParenthesizedExpression() {
        delete expr;
    }
    
    virtual int getSizeOf(Context& context) const {
        return expr->getSizeOf(context);
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<"(";
        expr->printPy(dst, indentLevel, GlobalIdentifiers);
        dst<<")";
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        expr->printMIPS(dst, context, destReg);
    }
};


#endif
