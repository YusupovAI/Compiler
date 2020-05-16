#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Stack.h"

class SymbolTable {
 public:
  void Put(const std::string& symbol, char* data, size_t len);

  void CreateVariable(const std::string& symbol, const std::string& type, size_t len);

  bool HasVariable(const std::string& symbol) const;

  size_t GetVariableOffset(const std::string& symbol) const;

  char* GetVariable(const std::string& symbol);

  void BeginScope();

  void EndScope();

  SymbolTable();

  Stack& GetStack();

  const std::string& GetType(const std::string var_name) const;

 private:
  std::unordered_map<std::string, std::vector<std::pair<size_t, std::string> > > values_;
  std::vector<std::string> symbols_;
  Stack stack_;
};
