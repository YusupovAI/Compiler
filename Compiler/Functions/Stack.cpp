#include "Stack.h"

Stack::Stack(size_t size, size_t capacity, std::vector<size_t> offsets, std::vector<char> buffer)
: size_(size), capacity_(capacity), offsets_(std::move(offsets)), buffer_(std::move(buffer)) {}

Stack Stack::MakeStack() {
  return Stack(0, 4096, std::vector<size_t>(1), std::vector<char>(4096));
}

size_t Stack::Allocate(size_t size) {
  buffer_.resize(size_ + size);
  size_t result = size_;
  size_ += size;
  return result;
}

void Stack::BeginScope() {
  offsets_.push_back(size_);
}

void Stack::EndScope() {
  buffer_.resize(offsets_.back());
  offsets_.pop_back();
}

char *Stack::GetPointer(size_t idx) {
  return buffer_.data() + idx;
}





