#include "ExpressionOr.h"
#include "Visitor.h"

namespace AST {

ExpressionOr::ExpressionOr(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionOr::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionOr::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionOr::GetRight() const {
  return right_;
}

} // namespace AST