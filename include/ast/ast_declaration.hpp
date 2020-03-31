#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include <string>
#include <iostream>

class Context;

class Declaration : public ASTNode {
private:
    ASTNode* specifiers;
    std::string* identifier;
    Expression* initializer;

public:
    Declaration(ASTNode* _specifiers, std::string* _identifier, Expression* _initializer) : specifiers(_specifiers), identifier(_identifier), initializer(_initializer) {}
    virtual ~Declaration() {
        delete specifiers;
        delete identifier;
        if (initializer != NULL) delete initializer;
    };
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        if (indentLevel == 0){
            GlobalIdentifiers.push_back(*identifier);
        }
        dst<<getIndent(indentLevel);
        // specifiers->printPy(dst);
        dst<<*identifier;
        if (initializer == NULL) dst<<" = 0"; // TODO: change later
        else {
            dst<<"=";
            initializer->printPy(dst, indentLevel, GlobalIdentifiers);
        }
        dst<<std::endl;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (context.inFunction == true) { // local variable declaration
            context.addLocalVariable(*identifier);
            
            if (initializer != NULL){
                initializer->printMIPS(dst, context, destReg);
                dst<<"sw $"<<destReg<<", "<<context.localVarMap.at(*identifier)<<"($fp)"<<std::endl;
            } else {
                dst<<"sw $0, "<<context.localVarMap.at(*identifier)<<"($fp)"<<std::endl;
            }
        } else { // global variable declaration
            // context.globalVars.push_back(*identifier);
            
            int initialValue = 0;
            if (initializer != NULL){
                initialValue = initializer->evaluate(); // only works for constant initializers
            }
            dst<<".data"<<std::endl;
            dst<<".globl "<<*identifier<<std::endl;
            dst<<*identifier<<": .word "<<initialValue<<std::endl; // initialize value to 0
            dst<<".text"<<std::endl;
        }
    }
};

class PointerDeclaration : public Declaration {
private:

public:
    PointerDeclaration(ASTNode* _specifiers, std::string* _identifier, Expression* _initializer) : Declaration(_specifiers, _identifier, _initializer) {}
    virtual ~PointerDeclaration() {
    };
};

class ArrayInitializerList : public ASTNode {
public:
    std::vector<ExpressionPtr> initializers;
    ArrayInitializerList(ExpressionPtr _initializer) {
        initializers.push_back(_initializer);
    }
    
    virtual ~ArrayInitializerList() {
        for (auto initializer : initializers) {
            delete initializer;
        }
        initializers.clear();
    }
    
    ArrayInitializerList* insert(ExpressionPtr _initializer) {
        initializers.push_back(_initializer);
        return this;
    }
    
    void printConstantInitializerList(std::ostream &dst, int arrayLength) {
        std::string separator = "";
        for (auto initializer : initializers) {
            dst << separator << initializer->evaluate();
            separator = ",";
        }
        for (int i = initializers.size(); i < arrayLength; i++) {
            dst << separator << "0";
        }
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        
    }
};

class ArrayDeclaration : public ASTNode {
private:
    ASTNode* specifiers;
    std::string* identifier;
    Expression* arrayLength;
    ArrayInitializerList* initializerList;

public:
    ArrayDeclaration(ASTNode* _specifiers, std::string* _identifier, Expression* _arrayLength, ArrayInitializerList* _initializerList) : specifiers(_specifiers), identifier(_identifier), arrayLength(_arrayLength), initializerList(_initializerList) {}
    virtual ~ArrayDeclaration() {
        delete specifiers;
        delete identifier;
        if (arrayLength != NULL) delete arrayLength;
        if (initializerList != NULL) delete initializerList;
    };
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        if (context.inFunction == true) {
            context.addArray(*identifier, (int) arrayLength->evaluate());
            
            if (initializerList != NULL){
                int i;
                for (i = 0; i < (int) initializerList->initializers.size(); i++) {
                    dst<<"li $"<<destReg<<", "<<initializerList->initializers[i]->evaluate()<<std::endl;
                    dst<<"sw $"<<destReg<<", "<<context.localVarMap.at(*identifier)+4*i<<"($fp)"<<std::endl;
                }
                for (; i < (int) arrayLength->evaluate(); i++) {
                    // initialize remaining values to 0
                    dst<<"sw $0, "<<context.localVarMap.at(*identifier)+4*i<<"($fp)"<<std::endl;
                }
            } else {
                // leave values uninitialized
            }
        } else {
            // context.globalVars.push_back(*identifier);
            
            if (initializerList != NULL) {
                dst<<".data"<<std::endl;
                dst<<".globl "<<*identifier<<std::endl;
                dst<<*identifier<<": .word ";
                initializerList->printConstantInitializerList(dst, (int) arrayLength->evaluate());
                dst<<std::endl;
                dst<<".text"<<std::endl;
            } else {
                dst<<".data"<<std::endl;
                dst<<".globl "<<*identifier<<std::endl;
                dst<<*identifier<<": .word 0:"<<((int) arrayLength->evaluate())<<std::endl; // allocate a chunk of space in memory and initialize it to 0
                dst<<".text"<<std::endl;
            }
        }
    }
};

class Enumerator: public ASTNode{
protected:
    std::string* identifier;
    ExpressionPtr expr;
    
public:
    
    Enumerator(std::string* _identifier, ExpressionPtr _expr) : identifier(_identifier), expr(_expr) {}
    virtual ~Enumerator(){
        delete identifier;
        delete expr;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override{
        int value;
        if (expr != NULL) {
            value = (int) expr->evaluate();
            context.enumerator.previous_value = value;
        } else value = ++(context.enumerator.previous_value); // create struct in context
        if (context.inFunction == true ){
            context.addLocalVariable(*identifier);
            dst<<"li $"<<destReg<<", "<<value<<std::endl;
            dst<<"sw $"<<destReg<<", "<<context.localVarMap.at(*identifier)<<"($fp)"<<std::endl;
        }
        else {
            // context.globalVars.push_back(*identifier);
            dst<<".globl "<<*identifier<<std::endl;
            dst<<*identifier<<": .word "<<value<<std::endl;
        }
    }
};

class EnumeratorList: public ASTNode {
protected:
    std::vector<Enumerator*> enumerators;
public:
    EnumeratorList(Enumerator* _enumerator) {
        enumerators.push_back(_enumerator);
    }
    
    virtual ~EnumeratorList() {
        for (auto enumerator : enumerators) {
            delete enumerator;
        }
        enumerators.clear();
    }
    
    EnumeratorList* addNewEnumerator(Enumerator* _enumerator) {
        enumerators.push_back(_enumerator);
        return this;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (context.inFunction != true) dst<<".data"<<std::endl;
        for (auto enumerator : enumerators){
            enumerator->printMIPS(dst, context);
        }
        if (context.inFunction != true) dst<<".text"<<std::endl;
    }
};

class EnumSpecifier: public ASTNode {
protected:
    std::string* identifier;
    EnumeratorList* enumerators;
public:
    
    EnumSpecifier(std::string* _identifier, EnumeratorList* _enumerators) : identifier(_identifier), enumerators(_enumerators){}
        
    virtual ~EnumSpecifier(){
        delete identifier;
        delete enumerators;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
    //     if (context.inFuntion == true){
    //         //context.addEnum(*identifier, (int) enumerators->size());
    //         if (identifier != NULL)
    //     }
        if (enumerators != NULL) enumerators->printMIPS(dst, context);
    }
};

class EnumDeclaration : public Declaration {
protected:
    EnumSpecifier* enumSpecifier;
public:
    EnumDeclaration(EnumSpecifier* _enumSpecifier, std::string* _identifier, Expression* _initializer) : Declaration(new ASTSpecifierList("int"), _identifier, _initializer), enumSpecifier(_enumSpecifier) {
        
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        enumSpecifier->printMIPS(dst, context);
        Declaration::printMIPS(dst, context);
    }
};




#endif
