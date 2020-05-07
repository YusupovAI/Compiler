#include "ExpressionVariable.h"
#include "Visitor.h"

namespace AST {

ExpressionVariable::ExpressionVariable(std::string&& variable_name)
: variable_name_(std::move(variable_name)) {}

void ExpressionVariable::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::string& ExpressionVariable::GetVariableName() const {
  return variable_name_;
}

} // namespace AST