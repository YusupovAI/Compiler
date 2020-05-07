#include "ClassDeclarationSimple.h"
#include "Visitor.h"

namespace AST {

ClassDeclarationSimple::ClassDeclarationSimple(std::string&& class_name, std::unique_ptr<DeclarationList>&& declarations)
: class_name_(std::move(class_name)),
  declarations_(declarations.release()) {}

void ClassDeclarationSimple::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::string& ClassDeclarationSimple::GetClassName() const {
  return class_name_;
}

const std::unique_ptr<DeclarationList>& ClassDeclarationSimple::GetDeclarations() const {
  return declarations_;
}

} // namespace AST