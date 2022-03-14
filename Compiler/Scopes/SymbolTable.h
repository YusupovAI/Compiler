#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Stack.h"

class SymbolTable {
 public:
  void Put(const std::string& symbol, char* data);

  void CreateVariable(const std::string& symbol, const std::string& type, bool do_delete_);

  bool HasVariable(const std::string& symbol) const;

  size_t GetVariableOffset(const std::string& symbol) const;

  char* GetVariable(const std::string& symbol);

  void BeginScope();

  void EndScope();

  SymbolTable();

  Stack& GetStack();

  const std::string& GetVariableType(const std::string var_name) const;

 private:
  void Destruct(const std::string& symbol);

  struct SymbolInfo {
    SymbolInfo(std::string, size_t , bool);

    bool do_destruct_;
    size_t offset_;
    std::string type_;
  };

 private:
  std::unordered_map<std::string, std::vector<SymbolInfo> > values_;
  std::vector<std::string> symbols_;
  Stack stack_;
};
