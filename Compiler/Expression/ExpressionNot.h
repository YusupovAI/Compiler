#pragma once

#include "Expression.h"
#include <memory>

namespace AST {

class ExpressionNot : public Expression {
 public:
  ExpressionNot(std::unique_ptr<Expression>&& bool_expression);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetBoolExpression() const;

 private:
  std::unique_ptr<Expression> bool_expression_;
};

} // namespace AST