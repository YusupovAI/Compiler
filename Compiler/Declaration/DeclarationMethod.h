#pragma once

#include <memory>
#include "MethodDeclaration.h"
#include "Declaration.h"

namespace AST {

class DeclarationMethod : public Declaration {
 public:
  DeclarationMethod(std::unique_ptr<MethodDeclaration>&& declaration);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<MethodDeclaration>& GetDeclaration() const;

 private:
  std::unique_ptr<MethodDeclaration> declaration_;
};

} // namespace AST