#include "ExpressionArrayElement.h"
#include "Visitor.h"

namespace AST {

ExpressionArrayElement::ExpressionArrayElement(std::unique_ptr<Expression>&& array, std::unique_ptr<Expression>&& index)
: array_(array.release()),
  index_(index.release()) {}

void ExpressionArrayElement::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ExpressionArrayElement::GetArray() const {
  return array_;
}

const std::unique_ptr<Expression>& ExpressionArrayElement::GetIndex() const {
  return index_;
}

} // namespace AST