#include "ScopeLayer.h"

#include <stdexcept>

bool ScopeLayer::HasValue(const std::string& name) const {
  auto needed =  GetNeeded(name);
  if (needed->objects_.find(name) != needed->objects_.end()) {
    return needed->objects_.find(name)->second.HasValue();
  }
}

void ScopeLayer::DeclareVariable(const std::string& name, const std::string& typ) {
  if (IsDeclared(name)) {
    throw std::logic_error("Variable was previously declared");
  }
  objects_[name] = Object(typ);
}

bool ScopeLayer::IsDeclared(const std::string& name) const {
  return objects_.find(name) != objects_.end();
}

const Object& ScopeLayer::GetValue(const std::string& name) const {
  if (!HasValue(name)) {
    throw std::logic_error("Variable was not declared in scopes");
  }
  return GetNeeded(name)->objects_.find(name)->second;
}

ScopeLayer* ScopeLayer::GetNeeded(const std::string &name) {
  auto current = this;
  while (current != nullptr) {
    if (current->objects_.find(name) != current->objects_.end()) {
      return current;
    }
    current = current->parent_;
  }
  return current;
}

const ScopeLayer* ScopeLayer::GetNeeded(const std::string &name) const {
  auto current = this;
  while (current != nullptr) {
    if (current->objects_.find(name) != current->objects_.end()) {
      return current;
    }
    current = current->parent_;
  }
  return current;
}

ScopeLayer::ScopeLayer(ScopeLayer *parent) : parent_(parent) {}

void ScopeLayer::SetValue(const std::string& name, const Object & obj) {
  auto current = GetNeeded(name);
  if (current == nullptr) {
    throw std::logic_error("Usage of undeclared variable");
  }
  current->objects_[name] = obj;
}
