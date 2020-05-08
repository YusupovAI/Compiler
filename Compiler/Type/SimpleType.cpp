#include "SimpleType.h"
#include "Visitor.h"

namespace AST {

SimpleType::SimpleType(std::string&& complicated_type)
: type_(std::move(complicated_type)) {}

void SimpleType::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::string& SimpleType::GetType() const {
  return type_;
}

}