#pragma once

#include "Expression.h"
#include <memory>

namespace AST {

class ExpressionLength : public Expression {
 public:
  ExpressionLength(std::unique_ptr<Expression>&& lhs);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetLhs() const;

 private:
  std::unique_ptr<Expression> lhs_;
};

} // namespace AST