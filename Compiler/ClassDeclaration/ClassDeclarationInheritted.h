#pragma once

#include <string>
#include "DeclarationList.h"
#include <memory>
#include "ClassDeclaration.h"

namespace AST {

class ClassDeclarationInheritted : public ClassDeclaration {
 public:
  ClassDeclarationInheritted(std::string&& class_name, std::string&& parent_name, std::unique_ptr<DeclarationList>&& declarations);

  void Accept(Visitor& visitor) const override;

  const std::string& GetClassName() const;

  const std::string& GetParentName() const;

  const std::unique_ptr<DeclarationList>& GetDeclarations() const;

 private:
  std::string class_name_;
  std::string parent_name_;
  std::unique_ptr<DeclarationList> declarations_;
};

} // namespace AST