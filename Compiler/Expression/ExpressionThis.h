#pragma once

#include "Expression.h"

namespace AST {

class ExpressionThis : public Expression {
 public:
  ExpressionThis();

  void Accept(Visitor& visitor) const override;

 private:
};

} // namespace AST