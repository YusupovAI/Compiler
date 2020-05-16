#include "Function.h"

Function::Function(
    std::string returning_type,
    std::vector<Type> types,
    std::vector<std::string> formals,
    const AST::StatementList& statements)
: returning_type_(std::move(returning_type)),
types_(std::move(types)),
formals_(std::move(formals)),
statements_(statements) {}

const std::vector<typename Function::Type> &Function::GetTypes() const {
  return types_;
}

const std::vector<std::string>& Function::GetFormals() const {
  return formals_;
}

Function Function::MakeFunction(const std::string& class_name, const AST::MethodDeclaration &decl) {
  auto head = decl.GetFormals().get();
  std::vector<typename Function::Type> types;
  std::vector<std::string> formals;
  while (head->GetHeadType() != nullptr) {
    types.push_back(head->GetHeadType()->GetType());
    formals.push_back(head->GetHeadName());
    head = head->GetTail().get();
  }
  return Function(decl.GetReturnType()->GetType(),
          std::move(types),
          std::move(formals),
          *decl.GetStatements());
}

const std::string &Function::GetReturningType() const {
  return returning_type_;
}

const AST::StatementList &Function::GetStatements() const {
  return statements_;
}
