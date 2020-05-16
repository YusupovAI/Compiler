#include "ExpressionNewArray.h"
#include "Visitor.h"

namespace AST {

ExpressionNewArray::ExpressionNewArray(std::unique_ptr<Type>&& array_type, std::unique_ptr<Expression>&& array_size)
: array_type_(array_type.release()),
  array_size_(array_size.release()) {}

void ExpressionNewArray::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Type>& ExpressionNewArray::GetArrayType() const {
  return array_type_;
}

const std::unique_ptr<Expression>& ExpressionNewArray::GetArraySize() const {
  return array_size_;
}

} // namespace AST