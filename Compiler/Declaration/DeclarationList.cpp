#include "DeclarationList.h"
#include "Visitor.h"

namespace AST {

DeclarationList::DeclarationList(std::unique_ptr<Declaration>&& head, std::unique_ptr<DeclarationList>&& tail)
: head_(head.release()),
  tail_(tail.release()) {}

void DeclarationList::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Declaration>& DeclarationList::GetHead() const {
  return head_;
}

const std::unique_ptr<DeclarationList>& DeclarationList::GetTail() const {
  return tail_;
}

} // namespace AST