#include "ExpressionNewVariable.h"
#include "Visitor.h"

namespace AST {

ExpressionNewVariable::ExpressionNewVariable(std::string&& type_name)
: type_name_(std::move(type_name)) {}

void ExpressionNewVariable::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::string& ExpressionNewVariable::GetTypeName() const {
  return type_name_;
}

} // namespace AST