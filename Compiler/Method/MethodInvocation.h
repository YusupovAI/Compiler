#pragma once

#include "Expression.h"
#include <memory>
#include <string>
#include "FunctionArguments.h"
#include "TreeNode.h"

namespace AST {

class MethodInvocation : public TreeNode {
 public:
  MethodInvocation(std::unique_ptr<Expression>&& object, std::string&& method_name, std::unique_ptr<FunctionArguments>&& arguments);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Expression>& GetObject() const;

  const std::string& GetMethodName() const;

  const std::unique_ptr<FunctionArguments>& GetArguments() const;

 private:
  std::unique_ptr<Expression> object_;
  std::string method_name_;
  std::unique_ptr<FunctionArguments> arguments_;
};

} // namespace AST