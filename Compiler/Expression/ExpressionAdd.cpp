#include "ExpressionAdd.h"
#include "Visitor.h"

namespace AST {

ExpressionAdd::ExpressionAdd(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionAdd::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionAdd::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionAdd::GetRight() const {
  return right_;
}

} // namespace AST