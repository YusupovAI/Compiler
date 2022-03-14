#include "StatementWhile.h"
#include "Visitor.h"

namespace AST {

StatementWhile::StatementWhile(std::unique_ptr<Expression>&& condition, std::unique_ptr<Statement>&& body)
: condition_(condition.release()),
  body_(body.release()) {}

void StatementWhile::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& StatementWhile::GetCondition() const {
  return condition_;
}

const std::unique_ptr<Statement>& StatementWhile::GetBody() const {
  return body_;
}

} // namespace AST