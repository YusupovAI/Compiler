#include "ClassManager.h"

#include <stdexcept>

void ClassManager::AddClass(const std::string &class_name) {
  if (HasClass(class_name)) {
    throw std::logic_error("Redeclaration of class " + class_name);
  }
  classes_.insert(class_name);
}

bool ClassManager::HasClass(const std::string &class_name) const {
  return classes_.find(class_name) != classes_.end();
}
