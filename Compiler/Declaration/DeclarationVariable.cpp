#include "DeclarationVariable.h"
#include "Visitor.h"

namespace AST {

DeclarationVariable::DeclarationVariable(std::unique_ptr<VariableDeclaration>&& declaration)
: declaration_(declaration.release()) {}

void DeclarationVariable::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<VariableDeclaration>& DeclarationVariable::GetDeclaration() const {
  return declaration_;
}

} // namespace AST