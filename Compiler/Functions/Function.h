#pragma once

#include <string>
#include <vector>

#include "MethodDeclaration.h"

class FunctionSignature {
 public:
  using Type = std::string;

  FunctionSignature(std::vector<Type> types, std::vector<std::string> formals);

  const std::vector<Type>& GetTypes() const;

  const std::vector<std::string>& Formals() const;

  static FunctionSignature MakeFunction(AST::MethodDeclaration&);

 private:
  const std::vector<Type> types_;
  const std::vector<std::string> formals_;
};
