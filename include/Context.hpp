#ifndef context_hpp
#define context_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map> 

class Context{
public:
    std::map<std::string, int> localVarMap; // store identifier and internal stack pointer in the stack
    std::map<std::string, int> globalVarMap;
    
    // addVariable(std::ostream &dst) {
    //     dst<<"addi $s0, $s0, -4"<<std::endl;
    
    // }
    
    void pushToStack(std::ostream &dst, int registerNumber) {
        dst<<"addi $s0, $s0, -4"<<std::endl; // we will use $s0 as an internal stack pointer
        dst<<"sw $"<<registerNumber<<", 0($s0)"<<std::endl;
    }
    void popFromStack(std::ostream &dst, int registerNumber) {
        dst<<"lw $"<<registerNumber<<", 0($s0)"<<std::endl;
        dst<<"addi $s0, $s0, 4"<<std::endl;
    }
};


#endif
