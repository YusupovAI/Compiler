#pragma once

#include <vector>

class Stack {
 public:
  static Stack MakeStack();

  size_t Allocate(size_t size);

  void BeginScope();

  void EndScope();

  char* GetPointer(size_t);

 private:
  std::vector<size_t> offsets_;
  std::vector<char> buffer_;
  size_t size_;
  size_t capacity_;

  Stack(size_t size, size_t capacity, std::vector<size_t> offsets, std::vector<char> buffer);
};
