#include "SymbolTable.h"

void SymbolTable::Put(const std::string &symbol, char *data, size_t len) {
  size_t idx = values_[symbol].back().first;
  char* addr = (char*)stack_.GetPointer(idx);
  for (size_t i = 0; i < len; ++i) {
    addr[i] = data[i];
  }
}

void SymbolTable::CreateVariable(const std::string &symbol, const std::string& type_, size_t len) {
  values_[symbol].push_back({stack_.Allocate(len), type_});
  symbols_.push_back(symbol);
}

void SymbolTable::BeginScope() {
  symbols_.push_back("{");
  stack_.BeginScope();
}

void SymbolTable::EndScope() {
  while (symbols_.back() != "{") {
    values_[symbols_.back()].pop_back();
    symbols_.pop_back();
  }
  symbols_.pop_back();
  stack_.EndScope();
}

bool SymbolTable::HasVariable(const std::string &symbol) const {
  return values_.find(symbol) != values_.end();
}

size_t SymbolTable::GetVariableOffset(const std::string &symbol) const {
  return values_.at(symbol).back().first;
}

SymbolTable::SymbolTable() : stack_(Stack::MakeStack()){}

char *SymbolTable::GetVariable(const std::string &symbol) {
  return stack_.GetPointer(values_.at(symbol).back().first);
}

Stack &SymbolTable::GetStack() {
  return stack_;
}

const std::string& SymbolTable::GetType(const std::string var_name) const {
  return values_.at(var_name).back().second;
}