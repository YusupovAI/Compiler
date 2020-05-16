#include "driver.h"
#include "TreePrinter.h"
#include "Interpreter.h"
#include "TypeChecker.h"
#include "FunctionManagerCreator.h"
#include "ClassManagerCreator.h"

#include <memory>
#include <Visitor/Interpreter.h>

Driver::Driver()
: scanner_(*this),
  parser_(scanner_, *this) {}


int Driver::Parse(std::string_view filename) {
  filename_ = filename;
  location_.initialize(&filename_);
  std::ifstream input(filename_);
  scanner_.yyrestart(&input);
  return parser_();
}

void Driver::SetProgram(std::unique_ptr<Program>&& program) {
  program_ = std::move(program);
}

yy::location& Driver::GetLocation() {
  return location_;
}

void Driver::Drive() {
  if (printing_tree_) {
    TreePrinter printer(std::cout);
    program_->Accept(printer);
  }

  auto function_manager = FunctionManagerCreator::MakeFunctionManager(*program_);
  auto class_manager_ = ClassManagerCreator::MakeClassManager(*program_);
  class_manager_.AddClass("int");
  class_manager_.AddClass("boolean");
  TypeChecker checker(function_manager, class_manager_);

  program_->Accept(checker);
  if (interpreting_) {
    AST::Interpreter interpreter(std::cout, function_manager, class_manager_);
    program_->Accept(interpreter);
  }
}

void Driver::EnablePrintingTree() {
  printing_tree_ = true;
}

void Driver::EnableInterpreting() {
  interpreting_ = true;
}
