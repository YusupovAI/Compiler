#pragma once

#include "TreeNode.h"
#include "Expression.h"
#include <memory>

namespace AST {

class FunctionArguments : public TreeNode {
 public:
  FunctionArguments() = default;
  FunctionArguments(std::unique_ptr<Expression>&& head, std::unique_ptr<FunctionArguments>&& tail);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetHead() const;

  const std::unique_ptr<FunctionArguments>& GetTail() const;

 private:
  std::unique_ptr<Expression> head_;
  std::unique_ptr<FunctionArguments> tail_;
};

} // namespace AST