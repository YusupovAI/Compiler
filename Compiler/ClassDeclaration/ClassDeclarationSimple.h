#pragma once

#include "ClassDeclaration.h"
#include <string>
#include "DeclarationList.h"
#include <memory>

namespace AST {

class ClassDeclarationSimple : public ClassDeclaration {
 public:
  ClassDeclarationSimple(std::string&& class_name, std::unique_ptr<DeclarationList>&& declarations);

  void Accept(Visitor& visitor) const override;

  const std::string& GetClassName() const;

  const std::unique_ptr<DeclarationList>& GetDeclarations() const;

 private:
  std::string class_name_;
  std::unique_ptr<DeclarationList> declarations_;
};

} // namespace AST