#include "DeclarationMethod.h"
#include "Visitor.h"

namespace AST {

DeclarationMethod::DeclarationMethod(std::unique_ptr<MethodDeclaration>&& declaration)
: declaration_(declaration.release()) {}

void DeclarationMethod::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<MethodDeclaration>& DeclarationMethod::GetDeclaration() const {
  return declaration_;
}

} // namespace AST