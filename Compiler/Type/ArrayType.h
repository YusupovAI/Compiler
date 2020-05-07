#pragma once

#include "SimpleType.h"
#include "Type.h"
#include <memory>

namespace AST {

class ArrayType : public Type {
 public:
  ArrayType(std::unique_ptr<SimpleType>&& type);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<SimpleType>& GetType() const;

 private:
  std::unique_ptr<SimpleType> type_;
};

} // namespace AST