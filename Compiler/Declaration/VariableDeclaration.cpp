#include "VariableDeclaration.h"
#include "Visitor.h"

namespace AST {

VariableDeclaration::VariableDeclaration(std::unique_ptr<Type>&& variable_type, std::string&& variable_name)
: variable_type_(variable_type.release()),
  variable_name_(std::move(variable_name)) {}

void VariableDeclaration::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Type>& VariableDeclaration::GetVariableType() const {
  return variable_type_;
}

const std::string& VariableDeclaration::GetVariableName() const {
  return variable_name_;
}

} // namespace AST