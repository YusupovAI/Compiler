#pragma once

#include <string>
#include <map>
#include <memory>
#include <deque>

class TypesScopeLayer {
 public:
  TypesScopeLayer() = default;

  TypesScopeLayer(TypesScopeLayer* parent);

  void DeclareVariable(const std::string& name, const std::string& typ);

  bool IsDeclared(const std::string&) const;

  const std::string& GetType(const std::string&) const;

  TypesScopeLayer* GetParent() const;

 private:
  const TypesScopeLayer* GetNeeded(const std::string& name) const;

 private:
  std::map<std::string, std::pair<bool, std::string> > types_;
  TypesScopeLayer* parent_{nullptr};
};


