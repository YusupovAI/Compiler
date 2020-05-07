#pragma once

#include <memory>
#include "TreeNode.h"
#include "Type.h"

namespace AST {

class Formals : public TreeNode {
 public:
  Formals() = default;
  Formals(std::unique_ptr<Type>&& head_type, std::string&& head_name, std::unique_ptr<Formals>&& tail);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Type>& GetHeadType() const;

  const std::string& GetHeadName() const;

  const std::unique_ptr<Formals>& GetTail() const;

 private:
  std::unique_ptr<Type> head_type_;
  std::string head_name_;
  std::unique_ptr<Formals> tail_;
};

} // namespace AST