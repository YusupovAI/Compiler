#include "ClassDeclarationList.h"
#include "Visitor.h"

namespace AST {

ClassDeclarationList::ClassDeclarationList(std::unique_ptr<ClassDeclaration>&& head, std::unique_ptr<ClassDeclarationList>&& tail)
: head_(head.release()),
  tail_(tail.release()) {}

void ClassDeclarationList::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<ClassDeclaration>& ClassDeclarationList::GetHead() const {
  return head_;
}

const std::unique_ptr<ClassDeclarationList>& ClassDeclarationList::GetTail() const {
  return tail_;
}

} // namespace AST