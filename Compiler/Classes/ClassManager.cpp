#include "ClassManager.h"

#include <stdexcept>

void ClassManager::AddClass(const std::string &class_name, Class&& cl) {
  if (HasClass(class_name)) {
    throw std::logic_error("Redeclaration of class " + class_name);
  }
  classes_[class_name] = std::move(cl);
}

bool ClassManager::HasClass(const std::string &class_name) const {
  return classes_.find(class_name) != classes_.end();
}

const Class& ClassManager::GetClass(const std::string& class_name) const {
  if (!HasClass(class_name)) {
    throw std::logic_error("Usage of undeclared class " + class_name);
  }
  return classes_.find(class_name)->second;
}