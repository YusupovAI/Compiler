#pragma once

#include <map>
#include <string>
#include <fstream>
#include "scanner.h"
#include "parser.h"


class Driver {
 public:

   Driver();

   int Parse(const std::string& f);

   bool ContainsVariable(const std::string& variable_name) const;

   int GetVariableValue(const std::string& variable_name) const;

   void SetVariableValue(const std::string& variable_name, int new_value_);

   yy::location& GetLocation();

 private:
   std::ifstream stream_{};
   std::map<std::string, int> variables_{};
   Scanner scanner_;
   yy::parser parser_;
   yy::location location_{};
   std::string filename_{};
};
