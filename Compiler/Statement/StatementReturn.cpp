#include "StatementReturn.h"
#include "Visitor.h"

namespace AST {

StatementReturn::StatementReturn(std::unique_ptr<Expression>&& inner_expression)
: inner_expression_(inner_expression.release()) {}

void StatementReturn::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& StatementReturn::GetInnerExpression() const {
  return inner_expression_;
}

} // namespace AST