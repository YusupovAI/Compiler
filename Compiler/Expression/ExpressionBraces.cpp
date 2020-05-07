#include "ExpressionBraces.h"
#include "Visitor.h"

namespace AST {

ExpressionBraces::ExpressionBraces(std::unique_ptr<Expression>&& inner_expression)
: inner_expression_(inner_expression.release()) {}

void ExpressionBraces::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionBraces::GetInnerExpression() const {
  return inner_expression_;
}

} // namespace AST