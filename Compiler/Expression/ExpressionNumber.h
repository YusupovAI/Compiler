#pragma once

#include "Expression.h"

namespace AST {

class ExpressionNumber : public Expression {
 public:
  ExpressionNumber(int value);

  void Accept(Visitor&) const;

  int GetValue() const;
 private:
  int value_;
};

} // namespace AST