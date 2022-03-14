#pragma once

#include "TreeNode.h"
#include <string>

namespace AST {

class SimpleLValue : public TreeNode {
 public:
  SimpleLValue(std::string&& variable_name);

  void Accept(Visitor& visitor) const override;

  const std::string& GetVariableName() const;

 private:
  std::string variable_name_;
};

} // namespace AST