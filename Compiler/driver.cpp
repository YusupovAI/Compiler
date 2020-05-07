#include "driver.h"
#include "TreePrinter.h"
#include "MainInterpreter.h"

#include <memory>

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
  if (interpreting_) {
    MainInterpreter interpreter(std::cout);
    program_->Accept(interpreter);
  }
}

void Driver::EnablePrintingTree() {
  printing_tree_ = true;
}

void Driver::EnableInterpreting() {
  interpreting_ = true;
}
