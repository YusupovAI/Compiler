#include "ExpressionFalse.h"
#include "Visitor.h"

namespace AST {

ExpressionFalse::ExpressionFalse()
  {}

void ExpressionFalse::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

} // namespace AST