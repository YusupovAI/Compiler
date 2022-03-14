#include "FunctionManager.h"

#include <stdexcept>
#include <functional>

void FunctionManager::AddFunction(const std::string &class_name,
                                  const std::string &method_name,
                                  const AST::MethodDeclaration& method) {
  if (functions_.find({class_name, method_name}) != functions_.end()) {
    throw std::logic_error("Redeclaration of class method " + method_name + " of " + class_name + " class");
  }

  functions_.emplace(std::make_pair(class_name, method_name), Function::MakeFunction(class_name, method));
}

const Function &FunctionManager::GetFunction(const std::string &class_name, const std::string &method_name) const {
  auto it = functions_.find({class_name, method_name});
  if (it == functions_.end()) {
    throw std::logic_error("Trying to call " + method_name + " of class " + class_name);
  }
  return it->second;
}

size_t FunctionManager::HashFunction::operator()(const std::pair<std::string, std::string> &pair) const {
  return std::hash<std::string>()(pair.first) ^ std::hash<std::string>()(pair.second);
}
