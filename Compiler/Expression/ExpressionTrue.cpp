#include "ExpressionTrue.h"
#include "Visitor.h"

namespace AST {

ExpressionTrue::ExpressionTrue()
  {}

void ExpressionTrue::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

} // namespace AST