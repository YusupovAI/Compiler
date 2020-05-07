#include "Formals.h"
#include "Visitor.h"

namespace AST {

Formals::Formals(std::unique_ptr<Type>&& head_type, std::string&& head_name, std::unique_ptr<Formals>&& tail)
: head_type_(head_type.release()),
  head_name_(std::move(head_name)),
  tail_(tail.release()) {}

void Formals::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Type>& Formals::GetHeadType() const {
  return head_type_;
}

const std::string& Formals::GetHeadName() const {
  return head_name_;
}

const std::unique_ptr<Formals>& Formals::GetTail() const {
  return tail_;
}

} // namespace AST