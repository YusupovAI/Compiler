#pragma once

#include "LValue.h"
#include <string>
#include "SimpleLValue.h"
#include <memory>

namespace AST {

class LValueSimple : public LValue {
 public:
  LValueSimple(std::unique_ptr<SimpleLValue>&& lvalue);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<SimpleLValue>& GetLvalue() const;

 private:
  std::unique_ptr<SimpleLValue> lvalue_;
};

} // namespace AST