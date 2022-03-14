#pragma once

#include "Expression.h"

namespace AST {

class ExpressionTrue : public Expression {
 public:
  ExpressionTrue();

  void Accept(Visitor& visitor) const override;

 private:
};

} // namespace AST