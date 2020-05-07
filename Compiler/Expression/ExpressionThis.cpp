#include "ExpressionThis.h"
#include "Visitor.h"

namespace AST {

ExpressionThis::ExpressionThis()
  {}

void ExpressionThis::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

} // namespace AST