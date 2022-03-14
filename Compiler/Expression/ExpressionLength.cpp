#include "ExpressionLength.h"
#include "Visitor.h"

namespace AST {

ExpressionLength::ExpressionLength(std::unique_ptr<Expression>&& lhs)
: lhs_(lhs.release()) {}

void ExpressionLength::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionLength::GetLhs() const {
  return lhs_;
}

} // namespace AST