#include "MethodInvocation.h"
#include "Visitor.h"

namespace AST {

MethodInvocation::MethodInvocation(std::unique_ptr<Expression>&& object, std::string&& method_name, std::unique_ptr<FunctionArguments>&& arguments)
: object_(object.release()),
  method_name_(std::move(method_name)),
  arguments_(arguments.release()) {}

void MethodInvocation::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<Expression>& MethodInvocation::GetObject() const {
  return object_;
}

const std::string& MethodInvocation::GetMethodName() const {
  return method_name_;
}

const std::unique_ptr<FunctionArguments>& MethodInvocation::GetArguments() const {
  return arguments_;
}

} // namespace AST