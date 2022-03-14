#pragma once

#include "Expression.h"

namespace AST {

class ExpressionFalse : public Expression {
 public:
  ExpressionFalse();

  void Accept(Visitor& visitor) const override;

 private:
};

} // namespace AST