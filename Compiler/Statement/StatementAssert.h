#pragma once

#include "Expression.h"
#include <memory>
#include "Statement.h"

namespace AST {

class StatementAssert : public Statement {
 public:
  StatementAssert(std::unique_ptr<Expression>&& inner_expression);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetInnerExpression() const;

 private:
  std::unique_ptr<Expression> inner_expression_;
};

} // namespace AST