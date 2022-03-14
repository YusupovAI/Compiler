#include "LValueArrayElement.h"
#include "Visitor.h"

namespace AST {

LValueArrayElement::LValueArrayElement(std::unique_ptr<ArrayElementLValue>&& lvalue)
: lvalue_(lvalue.release()) {}

void LValueArrayElement::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<ArrayElementLValue>& LValueArrayElement::GetLvalue() const {
  return lvalue_;
}

} // namespace AST