#include "FunctionArguments.h"
#include "Visitor.h"

namespace AST {

FunctionArguments::FunctionArguments(std::unique_ptr<Expression>&& head, std::unique_ptr<FunctionArguments>&& tail)
: head_(head.release()),
  tail_(tail.release()) {}

void FunctionArguments::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& FunctionArguments::GetHead() const {
  return head_;
}

const std::unique_ptr<FunctionArguments>& FunctionArguments::GetTail() const {
  return tail_;
}

} // namespace AST