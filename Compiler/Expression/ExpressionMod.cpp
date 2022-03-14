#include "ExpressionMod.h"
#include "Visitor.h"

namespace AST {

ExpressionMod::ExpressionMod(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionMod::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionMod::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionMod::GetRight() const {
  return right_;
}

} // namespace AST