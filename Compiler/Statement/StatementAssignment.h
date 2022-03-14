#pragma once

#include "Expression.h"
#include <memory>
#include "Statement.h"
#include "LValue.h"

namespace AST {

class StatementAssignment : public Statement {
 public:
  StatementAssignment(std::unique_ptr<LValue>&& lhs, std::unique_ptr<Expression>&& rhs);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<LValue>& GetLhs() const;

  const std::unique_ptr<Expression>& GetRhs() const;

 private:
  std::unique_ptr<LValue> lhs_;
  std::unique_ptr<Expression> rhs_;
};

} // namespace AST