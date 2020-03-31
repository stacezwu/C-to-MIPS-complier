#ifndef context_hpp
#define context_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map> 
#include <stack>
#include <utility>

class FunctionDefinitionOrDeclaration;

class Context { // Each function call should have its own Context object
private:
    int internalStackPointer; // Repesents an internal 'stack pointer' for each function
                          // The address of the last element pushed to the stack/frame within a function will be ($fp+internalStackPointer)
                          // So this variable is not really a 'stack pointer', it's more of an 'offset' value than a 'pointer'
    int internalArgumentStackPointer;
    static int labelCnt;
public:
    int frameSize;
    bool inFunction = false;
    // Context* parentContext; TODO
    std::string functionName;
    Context() {
    }
    Context(int _frameSize, std::string _functionName) {
        inFunction = true;
        frameSize = _frameSize;
        functionName = _functionName;
        internalStackPointer = frameSize-8; // 2 things may be stored at the top of the frame: $ra, $fp
        internalArgumentStackPointer = 0;
    }
    
    // static std::map<std::string, FunctionDefinitionOrDeclaration*> allFunctions;
    
    std::vector<std::string> parameters;
    std::map<std::string, int> localVarMap; // store identifier and internal stack pointer in the stack
    static std::vector<std::string> globalVars;
    //struct stmntFlag{
    std::stack<std::string> breakStatement;
    std::stack<std::string> continueStatement;
    //};
    struct Enumerator{
        int previous_value = -1;
    } enumerator;
    
    struct SwitchCases{
        bool end = false;
        std::vector<std::pair<std::string, int>> caseMap;
    } switchcases;
    // void pushtobreakStatement(std::string label){
    //     breakStatement.push(label);
    // }
    
    void pushtocontinueStatement(std::string label){
        continueStatement.push(label);
    }
    
    // std::string popfrombreakStatement(std::ostream &dst){
    //     if(!breakStatement.empty()){
    //         std::string break_label = breakStatement.top();
    //         breakStatement.pop();
    //         // dst<<breakStatement.top()<<":"<<std::endl;
    //         return break_label;
    //     } else {
    //         return "";
    //     }
    // }
    
    void popfromcontinueStatement(std::ostream &dst){
        if (!continueStatement.empty()){
            dst<<continueStatement.top()<<":"<<std::endl;
            continueStatement.pop();    
        }
    }
    
    void addLocalVariable(std::string identifier) {
        internalStackPointer -= 4;
        localVarMap.insert({identifier, internalStackPointer});
    }
    
    void addParameter(std::string identifier) {
        addLocalVariable(identifier);
        parameters.push_back(identifier);
    }
    
    void addArray(std::string identifier, int length) {
        internalStackPointer -= 4*length; // assuming the previous element in the stack is 4 bytes long
        localVarMap.insert({identifier, internalStackPointer});
    }
    
    void pushToStack(std::ostream &dst, int registerNumber) {
        internalStackPointer -= 4;
        dst<<"sw $"<<registerNumber<<", "<<internalStackPointer<<"($fp)"<<std::endl;
    }
    void popFromStack(std::ostream &dst, int registerNumber) {
        dst<<"lw $"<<registerNumber<<", "<<internalStackPointer<<"($fp)"<<std::endl;
        internalStackPointer += 4;
    }
    
    static std::string makeLabel(std::string name){
        labelCnt++;
        return name+"."+std::to_string(labelCnt);
    }
    
};

#endif
