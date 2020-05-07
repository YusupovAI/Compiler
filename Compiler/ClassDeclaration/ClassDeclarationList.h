#pragma once

#include <memory>
#include "ClassDeclaration.h"

namespace AST {

class ClassDeclarationList : public TreeNode {
 public:
  ClassDeclarationList() = default;
  ClassDeclarationList(std::unique_ptr<ClassDeclaration>&& head, std::unique_ptr<ClassDeclarationList>&& tail);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<ClassDeclaration>& GetHead() const;

  const std::unique_ptr<ClassDeclarationList>& GetTail() const;

 private:
  std::unique_ptr<ClassDeclaration> head_;
  std::unique_ptr<ClassDeclarationList> tail_;
};

} // namespace AST