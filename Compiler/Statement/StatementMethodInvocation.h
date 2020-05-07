#pragma once

#include "MethodInvocation.h"
#include <memory>
#include "Statement.h"

namespace AST {

class StatementMethodInvocation : public Statement {
 public:
  StatementMethodInvocation(std::unique_ptr<MethodInvocation>&& method);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<MethodInvocation>& GetMethod() const;

 private:
  std::unique_ptr<MethodInvocation> method_;
};

} // namespace AST