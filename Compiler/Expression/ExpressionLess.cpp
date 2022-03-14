#include "ExpressionLess.h"
#include "Visitor.h"

namespace AST {

ExpressionLess::ExpressionLess(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionLess::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionLess::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionLess::GetRight() const {
  return right_;
}

} // namespace AST