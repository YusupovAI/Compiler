#pragma once

#include "Expression.h"
#include <memory>

namespace AST {

class ExpressionLess : public Expression {
 public:
  ExpressionLess(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetLeft() const;

  const std::unique_ptr<Expression>& GetRight() const;

 private:
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

} // namespace AST