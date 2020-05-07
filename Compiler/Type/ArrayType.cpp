#include "ArrayType.h"
#include "Visitor.h"

namespace AST {

ArrayType::ArrayType(std::unique_ptr<SimpleType>&& type)
: type_(type.release()) {}

void ArrayType::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<SimpleType>& ArrayType::GetType() const {
  return type_;
}

} // namespace AST