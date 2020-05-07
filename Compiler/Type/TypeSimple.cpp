#include "TypeSimple.h"
#include "Visitor.h"

namespace AST {

TypeSimple::TypeSimple(std::unique_ptr<SimpleType>&& type)
: type_(type.release()) {}

void TypeSimple::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<SimpleType>& TypeSimple::GetType() const {
  return type_;
}

} // namespace AST