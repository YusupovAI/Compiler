#include "SimpleType.h"
#include "Visitor.h"

namespace AST {

SimpleType::SimpleType(SimpleType::Primitive primitive_type)
: type_(primitive_type) {}

SimpleType::SimpleType(std::string&& complicated_type)
: type_(std::move(complicated_type)) {}

void SimpleType::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::variant<typename SimpleType::Primitive, std::string>& 
SimpleType::GetType() const {
  return type_;
}

}