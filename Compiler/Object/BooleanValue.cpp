#include "BooleanValue.h"

BooleanValue::BooleanValue(bool flag) : value_(flag) {}

bool BooleanValue::GetValue() const {
  return value_;
}
