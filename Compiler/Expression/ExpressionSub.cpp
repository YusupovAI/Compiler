#include "ExpressionSub.h"
#include "Visitor.h"

namespace AST {

ExpressionSub::ExpressionSub(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionSub::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionSub::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionSub::GetRight() const {
  return right_;
}

} // namespace AST