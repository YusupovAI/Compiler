#pragma once

#include <unordered_set>

class ClassManager {
 public:
  void AddClass(const std::string& class_name);

  bool HasClass(const std::string& class_name) const;

 private:
  std::unordered_set<std::string> classes_;
};
