#pragma once

#include "TreeNode.h"
#include <string>
#include "Type.h"
#include <memory>

namespace AST {

class VariableDeclaration : public TreeNode {
 public:
  VariableDeclaration(std::unique_ptr<Type>&& variable_type, std::string&& variable_name);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Type>& GetVariableType() const;

  const std::string& GetVariableName() const;

 private:
  std::unique_ptr<Type> variable_type_;
  std::string variable_name_;
};

} // namespace AST