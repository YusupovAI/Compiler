#pragma once

#include "TreeNode.h"

namespace AST {

class Declaration : public TreeNode {
 public:
  virtual ~Declaration() = default;
};

} // namespace AST