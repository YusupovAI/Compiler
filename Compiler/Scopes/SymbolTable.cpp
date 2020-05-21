#include "SymbolTable.h"
#include "SizeManager.h"

void SymbolTable::Put(const std::string &symbol, char *data) {
  size_t len = SizeManager::GetSize(values_[symbol].back().type_);
  size_t idx = values_[symbol].back().offset_;
  char *addr = (char *) stack_.GetPointer(idx);
  for (size_t i = 0; i < len; ++i) {
    addr[i] = data[i];
  }
}

void SymbolTable::BeginScope() {
  symbols_.push_back("{");
  stack_.BeginScope();
}

void SymbolTable::EndScope() {
  while (symbols_.back() != "{") {
    auto symbol = std::move(symbols_.back());
    Destruct(symbol);
    values_[symbol].pop_back();
    symbols_.pop_back();
  }
  symbols_.pop_back();
  stack_.EndScope();
}

bool SymbolTable::HasVariable(const std::string &symbol) const {
  return values_.find(symbol) != values_.end();
}

size_t SymbolTable::GetVariableOffset(const std::string &symbol) const {
  return values_.at(symbol).back().offset_;
}

SymbolTable::SymbolTable() : stack_(Stack::MakeStack()) {}

char *SymbolTable::GetVariable(const std::string &symbol) {
  return stack_.GetPointer(values_.at(symbol).back().offset_);
}

Stack &SymbolTable::GetStack() {
  return stack_;
}

const std::string &SymbolTable::GetVariableType(const std::string var_name) const {
  return values_.at(var_name).back().type_;
}

void SymbolTable::Destruct(const std::string &symbol) {
  if (!values_[symbol].back().do_destruct_) {
    return;
  }
  auto ty = GetVariableType(symbol);
  auto offset = GetVariableOffset(symbol);
  char *ptr = stack_.GetPointer(offset);
  if (ptr == nullptr) {
    return;
  }
  if (ty != "int" && ty != "boolean") {
    free(ptr);
  }
}

void SymbolTable::CreateVariable(const std::string &symbol, const std::string &type_, bool do_delete_ = false) {
  size_t len = SizeManager::GetSize(type_);
  values_[symbol].emplace_back(type_, stack_.Allocate(len), do_delete_);
  symbols_.push_back(symbol);
}

SymbolTable::SymbolInfo::SymbolInfo(std::string ty, size_t off, bool del)
    : type_(std::move(ty)), offset_(off), do_destruct_(del) {}
