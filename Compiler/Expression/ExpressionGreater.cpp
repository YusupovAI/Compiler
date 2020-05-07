#include "ExpressionGreater.h"
#include "Visitor.h"

namespace AST {

ExpressionGreater::ExpressionGreater(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionGreater::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionGreater::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionGreater::GetRight() const {
  return right_;
}

} // namespace AST