#pragma once

#include <unordered_map>

#include "Function.h"
#include "MethodDeclaration.h"

class FunctionManager {
 public:
  void AddFunction(const std::string& class_name, const std::string& method_name, const AST::MethodDeclaration& method);

  const Function& GetFunction(const std::string& class_name, const std::string& method_name) const;

 private:
  class HashFunction {
   public:
    size_t operator()(const std::pair<std::string, std::string>&) const;
  };

  std::unordered_map<std::pair<std::string, std::string> , Function, HashFunction> functions_;
};
