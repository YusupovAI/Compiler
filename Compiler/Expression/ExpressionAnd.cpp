#include "ExpressionAnd.h"
#include "Visitor.h"

namespace AST {

ExpressionAnd::ExpressionAnd(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionAnd::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionAnd::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionAnd::GetRight() const {
  return right_;
}

} // namespace AST