#include "StatementMethodInvocation.h"
#include "Visitor.h"

namespace AST {

StatementMethodInvocation::StatementMethodInvocation(std::unique_ptr<MethodInvocation>&& method)
: method_(method.release()) {}

void StatementMethodInvocation::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<MethodInvocation>& StatementMethodInvocation::GetMethod() const {
  return method_;
}

} // namespace AST