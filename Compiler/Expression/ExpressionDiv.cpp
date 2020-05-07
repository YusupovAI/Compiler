#include "ExpressionDiv.h"
#include "Visitor.h"

namespace AST {

ExpressionDiv::ExpressionDiv(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionDiv::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionDiv::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionDiv::GetRight() const {
  return right_;
}

} // namespace AST