#include "SimpleLValue.h"
#include "Visitor.h"

namespace AST {

SimpleLValue::SimpleLValue(std::string&& variable_name)
: variable_name_(std::move(variable_name)) {}

void SimpleLValue::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::string& SimpleLValue::GetVariableName() const {
  return variable_name_;
}

} // namespace AST