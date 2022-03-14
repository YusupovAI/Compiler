#pragma once

#include "Expression.h"
#include <memory>
#include "Statement.h"

namespace AST {

class StatementIfFull : public Statement {
 public:
  StatementIfFull(std::unique_ptr<Expression>&& condition, std::unique_ptr<Statement>&& true_body, std::unique_ptr<Statement>&& flase_body);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetCondition() const;

  const std::unique_ptr<Statement>& GetTrueBody() const;

  const std::unique_ptr<Statement>& GetFalseBody() const;

 private:
  std::unique_ptr<Expression> condition_;
  std::unique_ptr<Statement> true_body_;
  std::unique_ptr<Statement> flase_body_;
};

} // namespace AST