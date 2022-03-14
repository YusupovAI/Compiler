#pragma once

#include "Program.h"
#include "scanner.h"
#include "parser.h"
#include "Visitor.h"

#include <fstream>
#include <string_view>
#include <memory>
#include <deque>

class Driver {
 public:
  Driver();

  void Drive();

  int Parse(std::string_view file);

  yy::location& GetLocation();

  void SetProgram(std::unique_ptr<Program>&&);

  void EnablePrintingTree();

  void EnableInterpreting();

 private:
  yy::location location_{};
  std::ifstream stream_{};
  std::string filename_{};
  yy::parser parser_;
  Scanner scanner_;
  std::unique_ptr<Program> program_;
  bool printing_tree_{false};
  bool interpreting_{false};
};