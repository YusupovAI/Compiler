#include "ExpressionNot.h"
#include "Visitor.h"

namespace AST {

ExpressionNot::ExpressionNot(std::unique_ptr<Expression>&& bool_expression)
: bool_expression_(bool_expression.release()) {}

void ExpressionNot::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionNot::GetBoolExpression() const {
  return bool_expression_;
}

} // namespace AST