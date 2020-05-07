#pragma once

#include "Expression.h"
#include <memory>
#include "MethodInvocation.h"

namespace AST {

class ExpressionMethodInvocation : public Expression {
 public:
  ExpressionMethodInvocation(std::unique_ptr<MethodInvocation>&& method);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<MethodInvocation>& GetMethod() const;

 private:
  std::unique_ptr<MethodInvocation> method_;
};

} // namespace AST