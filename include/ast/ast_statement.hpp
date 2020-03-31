#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <iterator>

class Statement;
typedef const Statement* StatementPtr;

class Statement : public ASTNode {
public:
    virtual ~Statement() {};

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  = 0;
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {}
    
    virtual void LookUp(Context& context) const  {}; 
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
    
    virtual void LookUp(Context& context) const{
        for(auto blockItem : blockItems){
            blockItem->LookUp(context);
        }
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

    virtual void LookUp(Context& context)const {
        if (blockItemList != NULL) blockItemList->LookUp(context);
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        if (blockItemList != NULL) blockItemList->printPy(dst, indentLevel, GlobalIdentifiers);
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

    virtual void LookUp(Context& context)const{}
    
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
    
    virtual void LookUp(Context& context)const {}
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  {
        dst<<getIndent(indentLevel);
        dst<<"break"<<std::endl;
    };
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string breakstmnt = context.breakStatement.top();
        dst<<"b "<<breakstmnt<<std::endl;
        dst<<"nop"<<std::endl;
    }
};

class ContinueStatement : public Statement {
protected:
public:
    ContinueStatement() {}
    virtual ~ContinueStatement() {
    }
    
    //virtual void LookUp(Context& context) const override{}
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  {
        dst<<getIndent(indentLevel);
        dst<<"continue"<<std::endl;
    };

    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string cntstmnt = context.continueStatement.top();
        dst<<"b "<<cntstmnt<<std::endl;
        dst<<"nop"<<std::endl;
    }

};

class ReturnStatement : public Statement {
protected:
    Expression* expr;
public:
    ReturnStatement(Expression* _expr) : expr(_expr) {}
    virtual ~ReturnStatement() {
    }
    
    virtual void LookUp(Context& context)const {};

    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const  {
        dst<<getIndent(indentLevel);
        dst<<"return";
        if(expr != NULL) { dst<<" "; expr->printPy(dst, indentLevel, GlobalIdentifiers); }
        dst<<std::endl;
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        if(expr != NULL) expr->printMIPS(dst, context, 2);
        dst<<"j "<<context.functionName<<"_end_label"<<std::endl;
        dst<<"nop"<<std::endl;
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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string fail = context.makeLabel("iffalse");
        expr->printMIPS(dst, context, 2);
        dst<<"beq $2, $0, "<<fail<<std::endl;
        dst<<"nop"<<std::endl;
        statement->printMIPS(dst, context, destReg);
        dst<<fail<<":"<<std::endl;
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
    
    //virtual void LookUp(Context& context) const override{}
    

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
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string fail = context.makeLabel("iffalse");
        std::string pass = context.makeLabel("iftrue");
        expr->printMIPS(dst, context, 2);
        dst<<"beq $2, $0, "<<fail<<std::endl;
        dst<<"nop"<<std::endl;
        truestatement->printMIPS(dst, context, destReg);
        dst<<"b "<<pass<<std::endl;
        dst<<fail<<":"<<std::endl;
        falsestatement->printMIPS(dst, context, destReg);
        dst<<pass<<":"<<std::endl;
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
    
    //virtual void LookUp(Context& context) const override{}
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {
        dst<<getIndent(indentLevel);
        dst<<"while ";
        expr->printPy(dst, indentLevel, GlobalIdentifiers);
        dst<<":"<<std::endl;
        statement->printPy(dst, indentLevel+1, GlobalIdentifiers);
    }
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string fail = context.makeLabel("whilefalse");
        std::string pass = context.makeLabel("whiletrue");
        
        std::string breakstmnt = context.makeLabel("whilebreak");
        std::string continuestmnt = context.makeLabel("whilecontinue");
        context.breakStatement.push(breakstmnt);
        context.continueStatement.push(continuestmnt);
        
        dst<<"b "<<fail<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<pass<<":"<<std::endl;
        statement->printMIPS(dst, context, destReg);
        dst<<continuestmnt<<":"<<std::endl;
        dst<<fail<<":"<<std::endl;
        expr->printMIPS(dst, context);
        dst<<"bne $2, $0, "<<pass<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<breakstmnt<<":"<<std::endl;
        dst<<"nop"<<std::endl;
        
        context.breakStatement.pop();
        context.continueStatement.pop();
    }
};

class ForStatement: public Statement{
protected: 
    ExpressionPtr lexpr;
    ExpressionPtr mexpr;
    ExpressionPtr rexpr;
    StatementPtr statement;
public:
    ForStatement(ExpressionPtr _lexpr, ExpressionPtr _mexpr, ExpressionPtr _rexpr, StatementPtr _statement): lexpr(_lexpr), mexpr(_mexpr), rexpr(_rexpr), statement(_statement){}
    virtual ~ForStatement(){
        delete lexpr;
        delete mexpr;
        delete rexpr;
        delete statement;
    }
    
    //virtual void LookUp(Context& context) const override{}
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        std::string fail = context.makeLabel("forfalse");
        std::string pass = context.makeLabel("fortrue");
        
        std::string breakstmnt = context.makeLabel("forbreak");
        context.breakStatement.push(breakstmnt);
        std::string continuestmnt = context.makeLabel("forcontinue");
        context.continueStatement.push(continuestmnt);
        
        if (lexpr != NULL) lexpr->printMIPS(dst, context);
        dst<<"b "<<fail<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<pass<<":"<<std::endl;
        statement->printMIPS(dst, context);
        dst<<continuestmnt<<":"<<std::endl;
        if (rexpr != NULL) rexpr->printMIPS(dst, context);
        dst<<fail<<":"<<std::endl;
        if (mexpr != NULL) {
            mexpr->printMIPS(dst,context);
            dst<<"bne $2, $0,"<<pass<<std::endl; 
        }
        else dst<<"b "<<pass<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<breakstmnt<<":"<<std::endl;
        dst<<"nop"<<std::endl;
        
        context.breakStatement.pop();
        context.continueStatement.pop();
    }
};

class SwitchStatement: public Statement{
protected: 
    ExpressionPtr expr;
    StatementPtr statement;
public:
    SwitchStatement(ExpressionPtr _expr, StatementPtr _statement): expr(_expr), statement(_statement){}
    virtual ~SwitchStatement(){
        delete expr;
        delete statement;
    }
    
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
        
        std::string breakstmnt = context.makeLabel("switchbreak");
        context.breakStatement.push(breakstmnt);
        expr->printMIPS(dst, context);
        statement->LookUp(context);
        context.switchcases.end = true;
        for (unsigned int i = 0; i < context.switchcases.caseMap.size(); i++){
            if (context.switchcases.caseMap[i].second != -1){
                dst<<"li $3, "<< context.switchcases.caseMap[i].second <<std::endl;
                dst<<"beq $"<<destReg<<", $3, "<<context.switchcases.caseMap[i].first<<std::endl;
                dst<<"nop"<<std::endl;
            }
        }
        
        if (context.switchcases.defaultCase.second == true ){
            dst<<"b "<<context.switchcases.defaultCase.first<<std::endl;
            dst<<"nop"<<std::endl;
        }
        else {
            dst<<"b "<<breakstmnt<<std::endl;
            dst<<"nop"<<std::endl;
        }
        
        statement->printMIPS(dst, context);
        
        dst<<breakstmnt<<":"<<std::endl;
        //dst<<"nop"<<std::endl;
        context.breakStatement.pop();
    }
};

class CaseStatement:public Statement{
protected:
    ExpressionPtr expr;
    StatementPtr statement;
public:
    CaseStatement(ExpressionPtr _expr, StatementPtr _statement): expr(_expr), statement(_statement){}
    virtual ~CaseStatement(){
        delete expr;
        delete statement;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {
  
        if (context.switchcases.end==true ){
            std::string label = context.switchcases.caseMap.begin()->first;
            context.switchcases.caseMap.erase(context.switchcases.caseMap.begin());
            dst<<label<<":"<<std::endl;
            statement->printMIPS(dst, context);   
        }  
        else {
        }
    }
    
    virtual void LookUp(Context& context)const{
        std::string label = context.makeLabel("case");
        int value = (int) expr->evaluate();
        context.switchcases.caseMap.push_back({label, value});
    }
};

class DefaultCaseStatement :public Statement {
protected:
    StatementPtr statement;
public:
    DefaultCaseStatement (StatementPtr _statement): statement(_statement){}
    virtual ~DefaultCaseStatement(){
        delete statement;
    }
    
    virtual void printPy(std::ostream &dst, int indentLevel, std::vector<std::string>& GlobalIdentifiers) const override {}
    
    virtual void printMIPS(std::ostream &dst, Context& context,int destReg = 2) const override {

        dst<<context.switchcases.defaultCase.first<<":"<<std::endl;
        statement->printMIPS(dst, context);   
        
    }
    
    virtual void LookUp(Context& context) const {
        std::string label = context.makeLabel("switchdefault");
        context.switchcases.defaultCase.first = label;
        context.switchcases.defaultCase.second = true;
    }

};


#endif
