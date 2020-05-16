#pragma once

#include <unordered_map>
#include <string>

#include "DeclarationList.h"

class Class {
 public:
  void AddField(const std::string&, size_t len);

  size_t GetFieldOffset(const std::string&) const;

  static Class MakeClass(const AST::DeclarationList*);

 private:
  std::unordered_map<std::string, size_t> offsets_;
  size_t size_{0};
};
