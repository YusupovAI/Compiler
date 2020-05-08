#pragma once

#include <memory>
#include <string>

#include "Value.h"

class Object {
 public:
  Object() = default;

  [[nodiscard]] const std::string& GetType() const;

  explicit Object(std::string type__);

  [[nodiscard]] std::shared_ptr<Value> GetValue() const;

  void SetValue(std::unique_ptr<Value>&&);

  [[nodiscard]] bool HasValue() const;

 private:
  std::shared_ptr<Value> value_{nullptr};
  std::string type_;
};
