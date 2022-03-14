#pragma once

#include "TreeNode.h"
#include <memory>
#include "MainClass.h"
#include "ClassDeclarationList.h"

namespace AST {

class Program : public TreeNode {
 public:
  Program(std::unique_ptr<MainClass>&& main_class, std::unique_ptr<ClassDeclarationList>&& classes_declaration);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<MainClass>& GetMainClass() const;

  const std::unique_ptr<ClassDeclarationList>& GetClassesDeclaration() const;

 private:
  std::unique_ptr<MainClass> main_class_;
  std::unique_ptr<ClassDeclarationList> classes_declaration_;
};

} // namespace AST