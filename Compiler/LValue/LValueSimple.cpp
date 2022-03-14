#include "LValueSimple.h"
#include "Visitor.h"

namespace AST {

LValueSimple::LValueSimple(std::unique_ptr<SimpleLValue>&& lvalue)
: lvalue_(lvalue.release()) {}

void LValueSimple::Accept(Visitor& visitor) const {
  visitor.Visit(*this);
}

const std::unique_ptr<SimpleLValue>& LValueSimple::GetLvalue() const {
  return lvalue_;
}

} // namespace AST