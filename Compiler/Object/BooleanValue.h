#pragma once

#include "Value.h"

class BooleanValue : public Value {
 public:
  explicit BooleanValue(bool flag);

  [[nodiscard]] bool GetValue() const;

 private:
  bool value_;
};
