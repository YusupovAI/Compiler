#pragma once

#include "Expression.h"
#include <string>

namespace AST {

class ExpressionNewVariable : public Expression {
 public:
  ExpressionNewVariable(std::string&& type_name);

  void Accept(Visitor& visitor) const override;

  const std::string& GetTypeName() const;

 private:
  std::string type_name_;
};

} // namespace AST