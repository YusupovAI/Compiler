#include "ExpressionMul.h"
#include "Visitor.h"

namespace AST {

ExpressionMul::ExpressionMul(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionMul::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionMul::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionMul::GetRight() const {
  return right_;
}

} // namespace AST