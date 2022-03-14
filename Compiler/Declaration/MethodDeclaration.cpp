#include "MethodDeclaration.h"
#include "Visitor.h"

namespace AST {

MethodDeclaration::MethodDeclaration(std::unique_ptr<Type>&& return_type, std::string&& method_name, std::unique_ptr<Formals>&& formals, std::unique_ptr<StatementList>&& statements)
: return_type_(return_type.release()),
  method_name_(std::move(method_name)),
  formals_(formals.release()),
  statements_(statements.release()) {}

void MethodDeclaration::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Type>& MethodDeclaration::GetReturnType() const {
  return return_type_;
}

const std::string& MethodDeclaration::GetMethodName() const {
  return method_name_;
}

const std::unique_ptr<Formals>& MethodDeclaration::GetFormals() const {
  return formals_;
}

const std::unique_ptr<StatementList>& MethodDeclaration::GetStatements() const {
  return statements_;
}

} // namespace AST