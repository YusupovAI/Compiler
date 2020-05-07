#include "StatementList.h"
#include "Visitor.h"

namespace AST {

StatementList::StatementList(std::unique_ptr<Statement>&& head, std::unique_ptr<StatementList>&& tail)
: head_(head.release()),
  tail_(tail.release()) {}

void StatementList::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Statement>& StatementList::GetHead() const {
  return head_;
}

const std::unique_ptr<StatementList>& StatementList::GetTail() const {
  return tail_;
}

} // namespace AST