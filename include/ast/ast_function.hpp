#ifndef ast_function_hpp
#define ast_function_hpp

#include <string>
#include <iostream>

//class Parameter;
//class ParameterList;

// basic function definition with no parameters and other features
class FunctionDefinition : public ASTNode {
protected:
    ASTNode* typeSpecifier;
    std::string* functionName;
    ASTNode* parameterList;
    Statement* functionBody;
public:
    FunctionDefinition(ASTNode* _typeSpecifier, std::string* _functionName, ASTNode* _parameterList, Statement* _functionBody) : typeSpecifier(_typeSpecifier), functionName(_functionName), parameterList(_parameterList), functionBody(_functionBody) {}
    virtual ~FunctionDefinition() {
        delete typeSpecifier;
        delete functionName;
        delete parameterList;
        delete functionBody;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst << "def " << *functionName << "(";
        if (parameterList == NULL){}
        else {
            parameterList->printPy(dst, indentLevel, GlobalIdentifiers);
        }
        dst << "):" << std::endl;
        
        this->printGlobal(dst, indentLevel+1, GlobalIdentifiers);
        functionBody->printPy(dst, indentLevel+1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        // Allocate an arbitrarily large frame (64 bytes) on the stack
        dst << ".globl" << *functionName << std::endl;
        dst << *functionName << ":" << std::endl;
        dst << "addiu $sp,$sp,-64" << std::endl;
        dst << "sw $fp,60($sp)" << std::endl;
        dst << "move $fp,$sp" << std::endl;
        dst << "addiu $s0, $fp, 52" << std::endl; // initialize internal frame pointer to $fp+52
        functionBody->printMIPS(dst, context);
        dst << "move $sp,$fp" << std::endl;
        dst << "lw $fp,60($sp)" << std::endl;
        dst << "addiu $sp,$sp,64" << std::endl;
        dst << "j $31" << std::endl;
        dst << "nop" << std::endl;
    }
};


class Parameter: public ASTNode{
protected: 
    ASTNode* argumentTypeSpecifier;
    std::string* argumentIdentifier;
public: 
    Parameter(ASTNode* _argumentTypeSpecifier, std::string* _argumentIdentifier): argumentTypeSpecifier(_argumentTypeSpecifier), argumentIdentifier(_argumentIdentifier){}
    virtual ~Parameter(){
        delete argumentTypeSpecifier;
        delete argumentIdentifier;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override{
        dst<<*argumentIdentifier<<" ";
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {}
};


class ParameterList: public ASTNode{
protected:
    std::vector<ASTNode*> parameter_list;
public:
    ParameterList(ASTNode* _parameter){
        parameter_list.push_back(_parameter);
    }
    
    virtual ~ParameterList(){
        for (auto parameter : parameter_list){
            delete parameter;
        }
        parameter_list.clear();
    }
    
    ParameterList* addNewParameter(ASTNode* _parameter){
        parameter_list.push_back(_parameter);
        return this;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override{
        for (auto parameter : parameter_list){
            parameter->printPy(dst, indentLevel, GlobalIdentifiers);
            dst<<", ";
        }
        // dst<<parameter_list[parameterList.size()-1]->printPy(dst, indentLevel, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {}
};

#endif
