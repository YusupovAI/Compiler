#pragma once

#include <string>
#include <vector>

#include "StatementList.h"
#include "MethodDeclaration.h"

#include "TypesScopeLayer.h"

class Function {
 public:
  using Type = std::string;


  const std::vector<Type>& GetTypes() const;

  const std::vector<std::string>& GetFormals() const;

  const AST::StatementList& GetStatements() const;

  const std::string& GetReturningType() const;

  static Function MakeFunction(const std::string& class_name, const AST::MethodDeclaration&);
 private:
  Function(
      std::string return_type,
      std::vector<Type> types,
      std::vector<std::string> formals,
      const AST::StatementList&);

 private:
  const std::vector<Type> types_;
  const std::vector<std::string> formals_;
  const AST::StatementList& statements_;
  const std::string returning_type_;
};
