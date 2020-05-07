#include "ArrayElementLValue.h"
#include "Visitor.h"

namespace AST {

ArrayElementLValue::ArrayElementLValue(std::unique_ptr<Expression>&& array, std::unique_ptr<Expression>&& index)
: array_(array.release()),
  index_(index.release()) {}

void ArrayElementLValue::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& ArrayElementLValue::GetArray() const {
  return array_;
}

const std::unique_ptr<Expression>& ArrayElementLValue::GetIndex() const {
  return index_;
}

} // namespace AST