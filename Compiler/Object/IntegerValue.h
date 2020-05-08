#pragma once

#include "Value.h"

class IntegerValue : public Value {
 public:
  explicit IntegerValue(int);

  [[nodiscard]] int GetValue() const;

 private:
  int value_;
};
