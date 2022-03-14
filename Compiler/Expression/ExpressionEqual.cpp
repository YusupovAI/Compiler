#include "ExpressionEqual.h"
#include "Visitor.h"

namespace AST {

ExpressionEqual::ExpressionEqual(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right)
: left_(left.release()),
  right_(right.release()) {}

void ExpressionEqual::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionEqual::GetLeft() const {
  return left_;
}

const std::unique_ptr<Expression>& ExpressionEqual::GetRight() const {
  return right_;
}

} // namespace AST