#include "StatementPrint.h"
#include "Visitor.h"

namespace AST {

StatementPrint::StatementPrint(std::unique_ptr<Expression>&& inner_expression)
: inner_expression_(inner_expression.release()) {}

void StatementPrint::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& StatementPrint::GetInnerExpression() const {
  return inner_expression_;
}

} // namespace AST