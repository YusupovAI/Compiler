#pragma once

#include "ArrayType.h"
#include <memory>
#include "Type.h"

namespace AST {

class TypeArray : public Type {
 public:
  TypeArray(std::unique_ptr<ArrayType>&& type);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<ArrayType>& GetType() const;

 private:
  std::unique_ptr<ArrayType> type_;
};

} // namespace AST