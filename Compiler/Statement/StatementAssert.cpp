#include "StatementAssert.h"
#include "Visitor.h"

namespace AST {

StatementAssert::StatementAssert(std::unique_ptr<Expression>&& inner_expression)
: inner_expression_(inner_expression.release()) {}

void StatementAssert::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& StatementAssert::GetInnerExpression() const {
  return inner_expression_;
}

} // namespace AST