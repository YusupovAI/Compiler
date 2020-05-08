#pragma once

#include "Type.h"
#include <string>
#include <variant>

namespace AST {

class SimpleType : public Type {
 public:

  void Accept(Visitor&) const;

  const std::string& GetType() const;

  SimpleType(std::string&& compilcated_type);

 private:
  std::string type_;
};

} // namespace AST