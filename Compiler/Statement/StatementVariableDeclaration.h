#pragma once

#include "VariableDeclaration.h"
#include <memory>
#include "Statement.h"

namespace AST {

class StatementVariableDeclaration : public Statement {
 public:
  StatementVariableDeclaration(std::unique_ptr<VariableDeclaration>&& declaration);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<VariableDeclaration>& GetDeclaration() const;

 private:
  std::unique_ptr<VariableDeclaration> declaration_;
};

} // namespace AST