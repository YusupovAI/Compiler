#include "IntegerValue.h"


IntegerValue::IntegerValue(int value) : value_(value) {}

int IntegerValue::GetValue() const {
  return value_;
}