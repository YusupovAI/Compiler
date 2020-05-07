#pragma once

#include "SimpleType.h"
#include <memory>
#include "Type.h"

namespace AST {

class TypeSimple : public Type {
 public:
  TypeSimple(std::unique_ptr<SimpleType>&& type);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<SimpleType>& GetType() const;

 private:
  std::unique_ptr<SimpleType> type_;
};

} // namespace AST