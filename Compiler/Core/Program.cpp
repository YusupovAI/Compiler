#include "Program.h"
#include "Visitor.h"

namespace AST {

Program::Program(std::unique_ptr<MainClass>&& main_class, std::unique_ptr<ClassDeclarationList>&& classes_declaration)
: main_class_(main_class.release()),
  classes_declaration_(classes_declaration.release()) {}

void Program::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<MainClass>& Program::GetMainClass() const {
  return main_class_;
}

const std::unique_ptr<ClassDeclarationList>& Program::GetClassesDeclaration() const {
  return classes_declaration_;
}

} // namespace AST