#include "Context.hpp"

// std::map<std::string, FunctionDefinitionOrDeclaration*> Context::allFunctions;
std::vector<std::string> Context::globalVars;
int Context::labelCnt = 0;