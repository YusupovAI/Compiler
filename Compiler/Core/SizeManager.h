#pragma once

#include <string>

class SizeManager {
 public:
  static size_t GetSize(const std::string&);

  static size_t GetWordSize();
};
