#include "ExpressionNumber.h"
#include "Visitor.h"

namespace AST {

ExpressionNumber::ExpressionNumber(int value) : value_(value) {}

int ExpressionNumber::GetValue() const {
  return value_;
}

void ExpressionNumber::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

}