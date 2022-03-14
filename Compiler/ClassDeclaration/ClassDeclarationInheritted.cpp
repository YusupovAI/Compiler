#include "ClassDeclarationInheritted.h"
#include "Visitor.h"

namespace AST {

ClassDeclarationInheritted::ClassDeclarationInheritted(std::string&& class_name, std::string&& parent_name, std::unique_ptr<DeclarationList>&& declarations)
: class_name_(std::move(class_name)),
  parent_name_(std::move(parent_name)),
  declarations_(declarations.release()) {}

void ClassDeclarationInheritted::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::string& ClassDeclarationInheritted::GetClassName() const {
  return class_name_;
}

const std::string& ClassDeclarationInheritted::GetParentName() const {
  return parent_name_;
}

const std::unique_ptr<DeclarationList>& ClassDeclarationInheritted::GetDeclarations() const {
  return declarations_;
}

} // namespace AST