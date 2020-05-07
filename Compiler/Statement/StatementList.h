#pragma once

#include <memory>
#include "TreeNode.h"
#include "Statement.h"

namespace AST {

class StatementList : public TreeNode {
 public:
  StatementList() = default;
  StatementList(std::unique_ptr<Statement>&& head, std::unique_ptr<StatementList>&& tail);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Statement>& GetHead() const;

  const std::unique_ptr<StatementList>& GetTail() const;

 private:
  std::unique_ptr<Statement> head_;
  std::unique_ptr<StatementList> tail_;
};

} // namespace AST