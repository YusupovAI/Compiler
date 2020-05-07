#pragma once

#include "TreeNode.h"

namespace AST {

class Expression : public TreeNode {
 public:
  virtual ~Expression() = default;
};

} // namespace AST