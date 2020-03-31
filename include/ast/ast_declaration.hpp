#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include <string>
#include <iostream>

class Context;

class Declaration : public ASTNode {
protected:
    Expression* specifiers;
    std::string* identifier;
    Expression* initializer;

public:
    Declaration(Expression* _specifiers, std::string* _identifier, Expression* _initializer) : specifiers(_specifiers), identifier(_identifier), initializer(_initializer) {}
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
        specifiers->printMIPS(dst, context);
        int typeSize = specifiers->getSizeOf(context);
        
        if (context.inFunction == true) { // local variable declaration
            context.addLocalVariable(*identifier, typeSize);
            
            std::string store_instr;
            if (typeSize == 1) store_instr = "sb";
            else if (typeSize == 2) store_instr = "sh";
            else store_instr = "sw"; // for now assume size is 4
            
            if (initializer != NULL){
                initializer->printMIPS(dst, context, destReg);
                dst<<store_instr<<" $"<<destReg<<", "<<context.localVarOffsets.at(*identifier)<<"($fp)"<<std::endl;
            } else {
                dst<<store_instr<<" $0, "<<context.localVarOffsets.at(*identifier)<<"($fp)"<<std::endl;
            }
        } else { // global variable declaration
            // context.globalVars.push_back(*identifier);
            context.globalVarSizes.insert({*identifier, typeSize});
            
            int initialValue = 0;
            if (initializer != NULL){
                initialValue = initializer->evaluate(); // only works for constant initializers
            }
            dst<<".data"<<std::endl;
            dst<<".globl "<<*identifier<<std::endl;
            if (typeSize == 1) dst<<*identifier<<": .byte "<<initialValue<<std::endl;
            else if (typeSize == 2) dst<<*identifier<<": .half "<<initialValue<<std::endl;
            else dst<<*identifier<<": .word "<<initialValue<<std::endl; // initialize value to 0
            dst<<".text"<<std::endl;
        }
    }
};

class PointerDeclaration : public Declaration {
protected:
    ASTSpecifierList* specifiersPtrCopy;
public:
    PointerDeclaration(ASTSpecifierList* _specifiers, std::string* _identifier, Expression* _initializer) : specifiersPtrCopy(_specifiers), Declaration(_specifiers->insert(new ASTSpecifierList("pointer")), _identifier, _initializer) {
    }
    virtual ~PointerDeclaration() {
    };
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        int typeSize = specifiersPtrCopy->getPointerTypeSize();
        dst<<"#debug: pointer type size "<<typeSize<<std::endl;
        if (context.inFunction == true) {
            context.localPointers.insert(*identifier);
            context.localArrayTypeSizes.insert({*identifier, typeSize});
        } else {
            context.globalPointers.insert(*identifier);
            context.globalArrayTypeSizes.insert({*identifier, typeSize});
        }
        Declaration::printMIPS(dst, context, destReg);
    }
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
    Expression* specifiers;
    std::string* identifier;
    Expression* arrayLength;
    ArrayInitializerList* initializerList;

public:
    ArrayDeclaration(Expression* _specifiers, std::string* _identifier, Expression* _arrayLength, ArrayInitializerList* _initializerList) : specifiers(_specifiers), identifier(_identifier), arrayLength(_arrayLength), initializerList(_initializerList) {}
    virtual ~ArrayDeclaration() {
        delete specifiers;
        delete identifier;
        if (arrayLength != NULL) delete arrayLength;
        if (initializerList != NULL) delete initializerList;
    };
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context, int destReg = 2) const override {
        specifiers->printMIPS(dst, context);
        
        int typeSize = specifiers->getSizeOf(context);
        
        if (context.inFunction == true) {
            context.addArray(*identifier, (int) arrayLength->evaluate(), typeSize);
            
            if (initializerList != NULL){
                std::string store_instr;
                if (typeSize == 1) store_instr = "sb";
                else if (typeSize == 2) store_instr = "sh";
                else store_instr = "sw"; // for now assume size is 4
                
                int i;
                for (i = 0; i < (int) initializerList->initializers.size(); i++) {
                    dst<<"li $"<<destReg<<", "<<initializerList->initializers[i]->evaluate()<<std::endl;
                    dst<<store_instr<<" $"<<destReg<<", "<<context.localVarOffsets.at(*identifier)+typeSize*i<<"($fp)"<<std::endl;
                }
                for (; i < (int) arrayLength->evaluate(); i++) {
                    // initialize remaining values to 0
                    dst<<store_instr<<" $0, "<<context.localVarOffsets.at(*identifier)+typeSize*i<<"($fp)"<<std::endl;
                }
            } else {
                // leave values uninitialized
            }
        } else {
            // context.globalVars.push_back(*identifier);
            context.globalVarSizes.insert({*identifier, ((int) arrayLength->evaluate())*specifiers->getSizeOf(context)});
            context.globalArrayTypeSizes.insert({*identifier, specifiers->getSizeOf(context)});

            if (initializerList != NULL) {
                dst<<".data"<<std::endl;
                dst<<".globl "<<*identifier<<std::endl;
                if (typeSize == 1) dst<<*identifier<<": .byte ";
                else if (typeSize == 2) dst<<*identifier<<": .half ";
                else dst<<*identifier<<": .word ";
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
            context.addLocalVariable(*identifier, 4);
            dst<<"li $"<<destReg<<", "<<value<<std::endl;
            dst<<"sw $"<<destReg<<", "<<context.localVarOffsets.at(*identifier)<<"($fp)"<<std::endl;
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


class InitDeclarator {
public:
    std::string declaratorType;
    std::string* identifier;
    Expression* expr;
    ArrayInitializerList* arrayInitializerList;
    ASTNode* parameterList;
    
    InitDeclarator(std::string _declaratorType, std::string* _identifier, Expression* _expr, ArrayInitializerList* _arrayInitializerList, ASTNode* _parameterList) : declaratorType(_declaratorType), identifier(_identifier), expr(_expr), arrayInitializerList(_arrayInitializerList), parameterList(_parameterList) {
        declaratorType = _declaratorType;
    }
    ~InitDeclarator() {
        // delete identifier;
        // delete expr;
        // delete arrayInitializerList;
        // delete parameterList;
    }
};

class InitDeclaratorList : public ASTNode {
protected:
    std::vector<InitDeclarator*> initDeclarators;
    std::vector<ASTNode*> generatedDeclarations;

public:
    InitDeclaratorList(std::string _declaratorType, std::string* _identifier, Expression* _expr, ArrayInitializerList* _arrayInitializerList, ASTNode* _parameterList) {
        initDeclarators.push_back(new InitDeclarator(_declaratorType, _identifier, _expr, _arrayInitializerList, _parameterList));
    }
    virtual ~InitDeclaratorList() {
        for (auto _initDeclarator : initDeclarators) {
            delete _initDeclarator;
        }
        initDeclarators.clear();
        for (auto _generatedDeclaration : generatedDeclarations) {
            delete _generatedDeclaration;
        }
        generatedDeclarations.clear();
    }
    
    InitDeclaratorList* insert(InitDeclaratorList* initDeclaratorList) {
        for (auto _initDeclarator : initDeclaratorList->initDeclarators) {
            this->initDeclarators.push_back(_initDeclarator);
        }
        while(!initDeclaratorList->initDeclarators.empty()) {
            initDeclaratorList->initDeclarators.pop_back();
        }
        delete initDeclaratorList;
        return this;
    }
    
    ASTNode* generateDeclarations(ASTSpecifierList* specifiers) {
        for (auto _initDeclarator : initDeclarators) {
            if (_initDeclarator->declaratorType == "variable") {
                generatedDeclarations.push_back(new Declaration(specifiers, _initDeclarator->identifier, _initDeclarator->expr));
            } else if (_initDeclarator->declaratorType == "pointer") {
                generatedDeclarations.push_back(new PointerDeclaration(specifiers, _initDeclarator->identifier, _initDeclarator->expr));
            } else if (_initDeclarator->declaratorType == "array") {
                generatedDeclarations.push_back(new ArrayDeclaration(specifiers, _initDeclarator->identifier, _initDeclarator->expr, _initDeclarator->arrayInitializerList));
            } else if (_initDeclarator->declaratorType == "function") {
                generatedDeclarations.push_back(new FunctionDeclaration(specifiers, _initDeclarator->identifier, _initDeclarator->parameterList));
            }

            delete _initDeclarator;
        }
        return this;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        for (auto _generatedDeclaration : generatedDeclarations) {
            _generatedDeclaration->printPy(dst, indentLevel, GlobalIdentifiers);
        }
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        for (auto _generatedDeclaration : generatedDeclarations) {
            _generatedDeclaration->printMIPS(dst, context);
        }
    }
};

class StructDeclaratorList: public ASTNode{
protected:
    std::vector<ASTNode*> structDeclarators;

public: 
    StructDeclaratorList(ASTNode* _declarator){
        structDeclarators.push_back(_declarator);
    }
    virtual ~StructDeclaratorList(){
         for (auto declarator : structDeclarators){
             delete declarator;                
         }
         structDeclarators.clear();
     }
    

    StructDeclaratorList* addNewStructDeclarator(ASTNode*_declarator){
        structDeclarators.push_back(_declarator);
        return this;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        for (auto declarator : structDeclarators){
            declarator->printMIPS(dst, context);
        }
    }
    
};

class StructSpecifier : public ASTNode{
protected:
    std::string* identifier;
    StructDeclaratorList* declarators;
public:
    StructSpecifier(std::string* _identifier, StructDeclaratorList* _declarators): identifier(_identifier), declarators(_declarators){}
    virtual ~StructSpecifier(){
        delete identifier;
        delete declarators;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (declarators != NULL) declarators->printMIPS(dst, context);
    }
};


#endif
