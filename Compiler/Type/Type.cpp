#include "Type.h"
#include "Visitor.h"

namespace AST {

Type::Type(std::string t) : type_(std::move(t)) {}

const std::string& Type::GetType() const {
  return type_;
}

void Type::Accept(Visitor &visitor) const {
  visitor.Visit(*this);
}

}