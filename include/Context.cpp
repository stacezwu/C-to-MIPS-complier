#include "Context.hpp"

int Context::stringLiteralCount = 0;

// std::map<std::string, FunctionDefinitionOrDeclaration*> Context::allFunctions;
std::vector<std::string> Context::globalVars;
std::map<std::string, int> Context::globalVarSizes;
std::map<std::string, int> Context::globalArrayTypeSizes;
std::set<std::string> Context::globalPointers;
int Context::labelCnt = 0;