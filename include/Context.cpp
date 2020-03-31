#include "Context.hpp"

// std::map<std::string, FunctionDefinitionOrDeclaration*> Context::allFunctions;
std::vector<std::string> Context::globalVars;
std::map<std::string, int> Context::globalVarSizes;
int Context::labelCnt = 0;