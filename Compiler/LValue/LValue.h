#pragma once

#include "TreeNode.h"

namespace AST {

class LValue : public TreeNode {
 public:
  virtual ~LValue() = default;
};

} // namespace AST