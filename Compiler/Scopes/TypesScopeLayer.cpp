#include "TypesScopeLayer.h"

#include <stdexcept>


void TypesScopeLayer::DeclareVariable(const std::string &name, const std::string &typ) {
  if (types_.find(name) != types_.end()) {
    throw std::logic_error("Variable" + name + " was previously declared");
  }
  types_[name] = {false, typ};
}
bool TypesScopeLayer::IsDeclared(const std::string &name) const {
  return GetNeeded(name) != nullptr;
}
const std::string &TypesScopeLayer::GetType(const std::string& name) const {
  const TypesScopeLayer* current = GetNeeded(name);
  if (current == nullptr) {
    throw std::logic_error("Usage of undeclared variable");
  }
  return current->types_.find(name)->second.second;
}

const TypesScopeLayer *TypesScopeLayer::GetNeeded(const std::string &name) const {
  const TypesScopeLayer* current = this;
  while (current != nullptr) {
    if (current->types_.find(name) != current->types_.end()) {
      return current;
    }
    current = current->parent_;
  }
  return nullptr;
}

TypesScopeLayer *TypesScopeLayer::GetParent() const {
  return parent_;
}

TypesScopeLayer::TypesScopeLayer(TypesScopeLayer *parent) : parent_(parent) {}
