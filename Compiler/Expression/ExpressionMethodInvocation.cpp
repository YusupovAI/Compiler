#include "ExpressionMethodInvocation.h"
#include "Visitor.h"

namespace AST {

ExpressionMethodInvocation::ExpressionMethodInvocation(std::unique_ptr<MethodInvocation>&& method)
: method_(method.release()) {}

void ExpressionMethodInvocation::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<MethodInvocation>& ExpressionMethodInvocation::GetMethod() const {
  return method_;
}

} // namespace AST