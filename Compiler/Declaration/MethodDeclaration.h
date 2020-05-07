#pragma once

#include "TreeNode.h"
#include "Type.h"
#include <memory>
#include "Formals.h"
#include "StatementList.h"

namespace AST {

class MethodDeclaration : public TreeNode {
 public:
  MethodDeclaration(std::unique_ptr<Type>&& return_type, std::string&& method_name, std::unique_ptr<Formals>&& formals, std::unique_ptr<StatementList>&& statements);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<Type>& GetReturnType() const;

  const std::string& GetMethodName() const;

  const std::unique_ptr<Formals>& GetFormals() const;

  const std::unique_ptr<StatementList>& GetStatements() const;

 private:
  std::unique_ptr<Type> return_type_;
  std::string method_name_;
  std::unique_ptr<Formals> formals_;
  std::unique_ptr<StatementList> statements_;
};

} // namespace AST