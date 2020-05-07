#pragma once

#include "Expression.h"
#include "SimpleType.h"
#include <memory>

namespace AST {

class ExpressionNewArray : public Expression {
 public:
  ExpressionNewArray(std::unique_ptr<SimpleType>&& array_type, std::unique_ptr<Expression>&& array_size);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<SimpleType>& GetArrayType() const;

  const std::unique_ptr<Expression>& GetArraySize() const;

 private:
  std::unique_ptr<SimpleType> array_type_;
  std::unique_ptr<Expression> array_size_;
};

} // namespace AST