#include "SizeManager.h"

size_t SizeManager::GetSize(const std::string &type_) {
  if (type_ == "int") {
    return 4;
  }
  if (type_ == "boolean") {
    return 1;
  }
  return 8;
}

size_t SizeManager::GetWordSize() {
  return 8;
}
