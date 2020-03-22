#include "driver.h"
#include "parser.h"
#include <fstream>

Driver::Driver()
: scanner_(*this),
  parser_(scanner_, *this) {}


int Driver::Parse(const std::string& filename) {
  filename_ = filename;
  location_.initialize(&filename_);
  std::ifstream input(filename_);
  scanner_.yyrestart(&input);
  return parser_();
}

bool Driver::ContainsVariable(const std::string& variable_name) const {
  return variables_.find(variable_name) != variables_.end();
}

int Driver::GetVariableValue(const std::string& variable_name) const {
  return variables_.at(variable_name);
}

void Driver::SetVariableValue(const std::string& variable_name, int new_value) {
  variables_[variable_name] = new_value;
}



yy::location& Driver::GetLocation() {
  return location_;
}