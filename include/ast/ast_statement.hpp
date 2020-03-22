#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <iostream>
#include <vector>

class Statement;
typedef const Statement* StatementPtr;

class Statement : public ASTNode {
public:
    virtual ~Statement() {};

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  = 0;
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {}
};


class BlockItemList : public ASTNodeList {
protected:
    std::vector<ASTNode*> blockItems;
public:
    BlockItemList(ASTNode* _blockItem) {
        blockItems.push_back(_blockItem);
    }
    
    virtual ~BlockItemList() {
        for (auto blockItem : blockItems) {
            delete blockItem;
        }
        blockItems.clear();
    }
    
    BlockItemList* insert(ASTNode* _node) {
        blockItems.push_back(_node);
        return this;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        for (auto blockItem : blockItems) {
            blockItem->printPy(dst, indentLevel, GlobalIdentifiers);
        }
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        for(auto blockItem : blockItems){
            blockItem->printMIPS(dst, context);
        }
    }
};


class CompoundStatement : public Statement {
protected:
    ASTNodeList* blockItemList;
public:
    CompoundStatement(ASTNodeList* _blockItemList) : blockItemList(_blockItemList) {}
    virtual ~CompoundStatement() {
        if (blockItemList != NULL) delete blockItemList;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        // dst<<"{"<<std::endl;
        if (blockItemList != NULL) blockItemList->printPy(dst, indentLevel, GlobalIdentifiers);
        // dst<<"}";
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if (blockItemList != NULL) blockItemList->printMIPS(dst, context);
    }
};

class ExpressionStatement : public Statement {
protected:
    ExpressionPtr expr;
public:
    ExpressionStatement(ExpressionPtr _expr) : expr(_expr) {}
    virtual ~ExpressionStatement() {
        delete expr;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<getIndent(indentLevel);
        expr->printPy(dst, indentLevel, GlobalIdentifiers);
        dst<<std::endl;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        expr->printMIPS(dst, context);
    }
    
};


class BreakStatement : public Statement {
protected:
public:
    BreakStatement() {}
    virtual ~BreakStatement() {
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  {
        dst<<getIndent(indentLevel);
        dst<<"break"<<std::endl;
    };
    

};

class ContinueStatement : public Statement {
protected:
public:
    ContinueStatement() {}
    virtual ~ContinueStatement() {
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  {
        dst<<getIndent(indentLevel);
        dst<<"continue"<<std::endl;
    };

};

class ReturnStatement : public Statement {
protected:
    Expression* expr;
public:
    ReturnStatement(Expression* _expr) : expr(_expr) {}
    virtual ~ReturnStatement() {
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  {
        dst<<getIndent(indentLevel);
        dst<<"return";
        if(expr != NULL) { dst<<" "; expr->printPy(dst, indentLevel, GlobalIdentifiers); }
        dst<<std::endl;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        expr->printMIPS(dst, context);
    }

};

class IfStatement : public Statement {
protected:
    ExpressionPtr expr;
    StatementPtr statement;
public:
    IfStatement(ExpressionPtr _expr, StatementPtr _statement) : expr(_expr), statement(_statement){}
    virtual ~IfStatement() {
        delete expr;
        delete statement;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<getIndent(indentLevel);
        dst<<"if ";
        expr->printPy(dst, indentLevel, GlobalIdentifiers);
        dst<<":"<<std::endl;
        statement->printPy(dst, indentLevel+1, GlobalIdentifiers);
        // dst<<std::endl; 
    }
};

class IfElseStatement : public Statement {
protected:
    ExpressionPtr expr;
    StatementPtr truestatement;
    StatementPtr falsestatement;
public:
    IfElseStatement(ExpressionPtr _expr, StatementPtr _truestatement, StatementPtr _falsestatement) : expr(_expr), truestatement(_truestatement), falsestatement(_falsestatement){}
    virtual ~IfElseStatement() {
        delete expr;
        delete truestatement;
        delete falsestatement;
    }

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<getIndent(indentLevel);
        dst<<"if ";
        expr->printPy(dst, indentLevel, GlobalIdentifiers);
        dst<<":"<<std::endl;
        truestatement->printPy(dst, indentLevel+1, GlobalIdentifiers);
        dst<<std::endl;
        dst<<getIndent(indentLevel);
        dst<<"else:"<<std::endl;
        falsestatement->printPy(dst, indentLevel+1, GlobalIdentifiers);
        // dst<<std::endl;
    }
};

class WhileStatement: public Statement{
protected: 
    ExpressionPtr expr;
    StatementPtr statement;
public:
    WhileStatement(ExpressionPtr _expr, StatementPtr _statement): expr(_expr), statement(_statement){}
    virtual ~WhileStatement(){
        delete expr;
        delete statement;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<getIndent(indentLevel);
        dst<<"while ";
        expr->printPy(dst, indentLevel, GlobalIdentifiers);
        dst<<":"<<std::endl;
        statement->printPy(dst, indentLevel+1, GlobalIdentifiers);
        // dst<<std::endl;
    }
};


#endif
