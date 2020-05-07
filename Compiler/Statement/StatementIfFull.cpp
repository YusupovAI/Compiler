#include "StatementIfFull.h"
#include "Visitor.h"

namespace AST {

StatementIfFull::StatementIfFull(std::unique_ptr<Expression>&& condition, std::unique_ptr<Statement>&& true_body, std::unique_ptr<Statement>&& flase_body)
: condition_(condition.release()),
  true_body_(true_body.release()),
  flase_body_(flase_body.release()) {}

void StatementIfFull::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& StatementIfFull::GetCondition() const {
  return condition_;
}

const std::unique_ptr<Statement>& StatementIfFull::GetTrueBody() const {
  return true_body_;
}

const std::unique_ptr<Statement>& StatementIfFull::GetFlaseBody() const {
  return flase_body_;
}

} // namespace AST