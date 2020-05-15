#pragma once

#include <string>
#include <unordered_map>
#include <optional>

#include "Object.h"

class TypesScopeLayer {
 public:
  TypesScopeLayer() = default;

  explicit ScopeLayer(ScopeLayer*);

  void DeclareVariable(const std::string& name, const std::string& typ);

  bool HasValue(const std::string&) const;

  bool IsDeclared(const std::string&) const;

  const std::string& GetType() const;

 private:
  ScopeLayer* GetNeeded(const std::string& name);

  const ScopeLayer* GetNeeded(const std::string&) const;

 private:
  std::unordered_map<std::string, std::string> types_:
  TypesScopeLayer* parent_{nullptr};
};


