#include "Object.h"

const std::string& Object::GetType() const {
  return type_;
}

Object::Object(std::string typ) : type_(std::move(typ)) {}

std::shared_ptr<Value> Object::GetValue() const {
  if (!HasValue()) {
    throw std::logic_error("Getting value of uninitialized object");
  }
  return value_;
}

void Object::SetValue(std::unique_ptr<Value>&& value) {
  value_ = std::move(value);
}

bool Object::HasValue() const {
  return value_ != nullptr;
}
