#include "StatementVariableDeclaration.h"
#include "Visitor.h"

namespace AST {

StatementVariableDeclaration::StatementVariableDeclaration(std::unique_ptr<VariableDeclaration>&& declaration)
: declaration_(declaration.release()) {}

void StatementVariableDeclaration::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<VariableDeclaration>& StatementVariableDeclaration::GetDeclaration() const {
  return declaration_;
}

} // namespace AST