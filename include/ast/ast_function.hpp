#ifndef ast_function_hpp
#define ast_function_hpp

#include <string>
#include <iostream>

//class Parameter;
//class ParameterList;

class FunctionDefinitionOrDeclaration : public ASTNode {
protected:
    Expression* typeSpecifier;
    std::string* functionName;
    ASTNode* parameterList;
public:
    Context* functionContext;
    
    FunctionDefinitionOrDeclaration(Expression* _typeSpecifier, std::string* _functionName, ASTNode* _parameterList) : typeSpecifier(_typeSpecifier), functionName(_functionName), parameterList(_parameterList) {
        // Context::allFunctions[*functionName] = this;
        functionContext = new Context(512, *functionName); // 512 bytes = frame size
    }
    virtual ~FunctionDefinitionOrDeclaration() {
        delete typeSpecifier;
        delete functionName;
        delete parameterList;
        delete functionContext;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {};
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {};
};

class FunctionDefinition : public FunctionDefinitionOrDeclaration {
protected:
    Statement* functionBody;
public:
    FunctionDefinition(Expression* _typeSpecifier, std::string* _functionName, ASTNode* _parameterList, Statement* _functionBody) : FunctionDefinitionOrDeclaration(_typeSpecifier, _functionName, _parameterList), functionBody(_functionBody) {}
    virtual ~FunctionDefinition() {
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
        typeSpecifier->printMIPS(dst, context);
        
        // Allocate an arbitrarily large frame (512 bytes) on the stack
        dst << ".globl " << *functionName << std::endl;
        dst << *functionName << ":" << std::endl;
        dst << "addiu $sp,$sp,-512" << std::endl;
        dst << "sw $fp,508($sp)" << std::endl;
        dst << "move $fp,$sp" << std::endl;
        dst << "sw $ra,504($sp)" << std::endl;
        // dst << "sw $s0,500($sp)" << std::endl;
        if (parameterList != NULL) parameterList->printMIPS(dst, *functionContext, 2); // treat parameters as locally declared variables
        functionBody->printMIPS(dst, *functionContext);
        dst << "li $2, 0" << std::endl; // implicit return 0 if no return statement was called - TODO: this only works for int
        dst << *functionName << "_end_label:" << std::endl;
        // dst << "lw $s0,500($sp)" << std::endl;
        dst << "lw $ra,504($sp)" << std::endl;
        dst << "move $sp,$fp" << std::endl;
        dst << "lw $fp,508($sp)" << std::endl;
        dst << "addiu $sp,$sp,512" << std::endl;
        dst << "j $31" << std::endl;
        dst << "nop" << std::endl;
    }
};

class FunctionDeclaration : public FunctionDefinitionOrDeclaration {
public:
    FunctionDeclaration(Expression* _typeSpecifier, std::string* _functionName, ASTNode* _parameterList) : FunctionDefinitionOrDeclaration(_typeSpecifier, _functionName, _parameterList) {}
    virtual ~FunctionDeclaration() {}

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        typeSpecifier->printMIPS(dst, context);
        dst << ".globl " << *functionName << std::endl;
    }
};


class Parameter: public ASTNode{
protected: 
    ASTSpecifierList* parameterTypeSpecifier;
    std::string* parameterIdentifier;
    bool isPointer;
public: 
    Parameter(ASTSpecifierList* _parameterTypeSpecifier, std::string* _parameterIdentifier, bool _isPointer) : parameterTypeSpecifier(_parameterTypeSpecifier), parameterIdentifier(_parameterIdentifier), isPointer(_isPointer) {}
    virtual ~Parameter(){
        delete parameterTypeSpecifier;
        delete parameterIdentifier;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override{
        dst<<*parameterIdentifier<<" ";
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        parameterTypeSpecifier->printMIPS(dst, context);
        context.addParameter(*parameterIdentifier, parameterTypeSpecifier->getSizeOf(context));
        
        if (isPointer) {
            int typeSize = parameterTypeSpecifier->getPointerTypeSize();
            context.localPointers.insert(*parameterIdentifier);
            context.localArrayTypeSizes.insert({*parameterIdentifier, typeSize});
        }
        

    }
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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        for (unsigned int i = 0; i < parameter_list.size(); i++){
            parameter_list[i]->printMIPS(dst, context);
            if (i < 4) {
                dst<<"sw $a"<<i<<", "<<context.localVarOffsets.at(context.parameters[i])<<"($fp)"<<std::endl;
            } else {
                dst<<"lw $2, "<<i*4+context.frameSize<<"($fp)"<<std::endl;
                dst<<"sw $2, "<<context.localVarOffsets.at(context.parameters[i])<<"($fp)"<<std::endl;
            }
        }
    }
};

#endif
