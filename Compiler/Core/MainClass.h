#pragma once

#include <string>
#include "TreeNode.h"
#include <memory>
#include "StatementList.h"

namespace AST {

class MainClass : public TreeNode {
 public:
  MainClass(std::string&& name, std::unique_ptr<StatementList>&& statements);

  void Accept(Visitor& visitor) const override;

  const std::string& GetName() const;

  const std::unique_ptr<StatementList>& GetStatements() const;

 private:
  std::string name_;
  std::unique_ptr<StatementList> statements_;
};

} // namespace AST