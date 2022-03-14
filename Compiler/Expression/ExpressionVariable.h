#pragma once

#include "Expression.h"
#include <string>

namespace AST {

class ExpressionVariable : public Expression {
 public:
  ExpressionVariable(std::string&& variable_name);

  void Accept(Visitor& visitor) const override;

  const std::string& GetVariableName() const;

 private:
  std::string variable_name_;
};

} // namespace AST