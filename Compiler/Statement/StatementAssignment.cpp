#include "StatementAssignment.h"
#include "Visitor.h"

namespace AST {

StatementAssignment::StatementAssignment(std::unique_ptr<LValue>&& lhs, std::unique_ptr<Expression>&& rhs)
: lhs_(lhs.release()),
  rhs_(rhs.release()) {}

void StatementAssignment::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<LValue>& StatementAssignment::GetLhs() const {
  return lhs_;
}

const std::unique_ptr<Expression>& StatementAssignment::GetRhs() const {
  return rhs_;
}

} // namespace AST