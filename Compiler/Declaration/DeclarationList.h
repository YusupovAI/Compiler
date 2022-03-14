#pragma once

#include "TreeNode.h"
#include <memory>
#include "Declaration.h"

namespace AST {

class DeclarationList : public TreeNode {
 public:
  DeclarationList() = default;
  DeclarationList(std::unique_ptr<Declaration>&& head, std::unique_ptr<DeclarationList>&& tail);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Declaration>& GetHead() const;

  const std::unique_ptr<DeclarationList>& GetTail() const;

 private:
  std::unique_ptr<Declaration> head_;
  std::unique_ptr<DeclarationList> tail_;
};

} // namespace AST