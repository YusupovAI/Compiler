#pragma once

#include "TreeNode.h"

namespace AST {

class ClassDeclaration : public TreeNode {
 public:
  virtual ~ClassDeclaration() = default;
};

} // namespace AST