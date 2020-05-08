#pragma once

#include <string>
#include <unordered_map>
#include <optional>

#include "Object.h"

class ScopeLayer {
 public:
  ScopeLayer() = default;

  explicit ScopeLayer(ScopeLayer*);

  void DeclareVariable(const std::string& name, const std::string& typ);

  bool HasValue(const std::string&) const;

  bool IsDeclared(const std::string&) const;

  const Object& GetValue(const std::string&) const;

  void SetValue(const std::string&, const Object&);

 private:
  ScopeLayer* GetNeeded(const std::string& name);

  const ScopeLayer* GetNeeded(const std::string&) const;

 private:
  std::unordered_map<std::string, Object> objects_;
  ScopeLayer* parent_{nullptr};
};


