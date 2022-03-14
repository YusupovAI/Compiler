#pragma once

#include "Expression.h"
#include <memory>

namespace AST {

class ExpressionArrayElement : public Expression {
 public:
  ExpressionArrayElement(std::unique_ptr<Expression>&& array, std::unique_ptr<Expression>&& index);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetArray() const;

  const std::unique_ptr<Expression>& GetIndex() const;

 private:
  std::unique_ptr<Expression> array_;
  std::unique_ptr<Expression> index_;
};

} // namespace AST