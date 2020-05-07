#pragma once

#include "TreeNode.h"

namespace AST {

class Statement : public TreeNode {
 public:
  virtual ~Statement() = default;
};

} // namespace AST