#pragma once

#include "Type.h"
#include <string>
#include <variant>

namespace AST {

class SimpleType : public Type {
 public:
  enum Primitive {
    Int,
    Boolean,
    Void, 
    None
  };

  void Accept(Visitor&) const;

  const std::variant<Primitive, std::string>& GetType() const;

  SimpleType(Primitive primitive_type);

  SimpleType(std::string&& compilcated_type);

 private:
  std::variant<Primitive, std::string> type_;
};

} // namespace AST