#include "StatementNewScope.h"
#include "Visitor.h"

namespace AST {

StatementNewScope::StatementNewScope(std::unique_ptr<StatementList>&& statements)
: statements_(statements.release()) {}

void StatementNewScope::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<StatementList>& StatementNewScope::GetStatements() const {
  return statements_;
}

} // namespace AST