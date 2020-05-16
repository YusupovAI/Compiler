#pragma once

#include "TreeNode.h"

#include <string>

namespace AST {

class Type : public TreeNode {
 public:
  Type(std::string);

  const std::string& GetType() const;

  void Accept(Visitor& visitor) const override;

 private:
  std::string type_;
};

} // namespace AST