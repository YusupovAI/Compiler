#pragma once

#include "TreeNode.h"

namespace AST {

class Type : public TreeNode {
 public:
  virtual ~Type() = default;
};

} // namespace AST