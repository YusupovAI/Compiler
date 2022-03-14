#pragma once

#include <unordered_map>
#include <string>

#include "DeclarationList.h"

class Class {
 public:
  void AddField(const std::string& name, const std::string& typ);

  size_t GetFieldOffset(const std::string&) const;

  static Class MakeClass(const AST::DeclarationList*);

  const std::string& GetFieldType(const std::string&) const;

  bool HasField(const std::string&) const;

  size_t GetSize() const;

 private:
  struct FieldInfo {
    FieldInfo() = default;

    FieldInfo(std::string, size_t);

    std::string type_;
    size_t offset_;
  };

 private:
  std::unordered_map<std::string, FieldInfo> offsets_;
  size_t size_{0};
};
