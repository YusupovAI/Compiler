#pragma once

namespace AST {

class Visitor;

class TreeNode {
 public:
  virtual void Accept(Visitor&) const = 0;

  virtual ~TreeNode(){};
};

}  // namespace AST