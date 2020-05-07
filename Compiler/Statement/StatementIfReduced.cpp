#include "StatementIfReduced.h"
#include "Visitor.h"

namespace AST {

StatementIfReduced::StatementIfReduced(std::unique_ptr<Expression>&& condition, std::unique_ptr<Statement>&& body)
: condition_(condition.release()),
  body_(body.release()) {}

void StatementIfReduced::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& StatementIfReduced::GetCondition() const {
  return condition_;
}

const std::unique_ptr<Statement>& StatementIfReduced::GetBody() const {
  return body_;
}

} // namespace AST