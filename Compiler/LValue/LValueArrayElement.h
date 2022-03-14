#pragma once

#include "LValue.h"
#include "Expression.h"
#include <memory>
#include "ArrayElementLValue.h"

namespace AST {

class LValueArrayElement : public LValue {
 public:
  LValueArrayElement(std::unique_ptr<ArrayElementLValue>&& lvalue);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<ArrayElementLValue>& GetLvalue() const;

 private:
  std::unique_ptr<ArrayElementLValue> lvalue_;
};

} // namespace AST