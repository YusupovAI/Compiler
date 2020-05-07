#pragma once

#include <memory>
#include "VariableDeclaration.h"
#include "Declaration.h"

namespace AST {

class DeclarationVariable : public Declaration {
 public:
  DeclarationVariable(std::unique_ptr<VariableDeclaration>&& declaration);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<VariableDeclaration>& GetDeclaration() const;

 private:
  std::unique_ptr<VariableDeclaration> declaration_;
};

} // namespace AST