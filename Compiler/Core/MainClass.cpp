#include "MainClass.h"
#include "Visitor.h"

namespace AST {

MainClass::MainClass(std::string&& name, std::unique_ptr<StatementList>&& statements)
: name_(std::move(name)),
  statements_(statements.release()) {}

void MainClass::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::string& MainClass::GetName() const {
  return name_;
}

const std::unique_ptr<StatementList>& MainClass::GetStatements() const {
  return statements_;
}

} // namespace AST