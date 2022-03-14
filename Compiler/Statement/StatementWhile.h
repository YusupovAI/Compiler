#pragma once

#include "Expression.h"
#include <memory>
#include "Statement.h"

namespace AST {

class StatementWhile : public Statement {
 public:
  StatementWhile(std::unique_ptr<Expression>&& condition, std::unique_ptr<Statement>&& body);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetCondition() const;

  const std::unique_ptr<Statement>& GetBody() const;

 private:
  std::unique_ptr<Expression> condition_;
  std::unique_ptr<Statement> body_;
};

} // namespace AST