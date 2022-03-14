#pragma once

#include <unordered_map>
#include "Class.h"

class ClassManager {
 public:
  void AddClass(const std::string& class_name, Class&&);

  bool HasClass(const std::string& class_name) const;

  const Class& GetClass(const std::string& class_name) const;

 private:
  std::unordered_map<std::string, Class> classes_;
};
