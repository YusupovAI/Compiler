#include "TypeArray.h"
#include "Visitor.h"

namespace AST {

TypeArray::TypeArray(std::unique_ptr<ArrayType>&& type)
: type_(type.release()) {}

void TypeArray::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<ArrayType>& TypeArray::GetType() const {
  return type_;
}

} // namespace AST