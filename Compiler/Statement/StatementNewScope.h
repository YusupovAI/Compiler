#pragma once

#include "StatementList.h"
#include <memory>
#include "Statement.h"

namespace AST {

class StatementNewScope : public Statement {
 public:
  StatementNewScope(std::unique_ptr<StatementList>&& statements);

  void Accept(Visitor& visitor) const override;

  const std::unique_ptr<StatementList>& GetStatements() const;

 private:
  std::unique_ptr<StatementList> statements_;
};

} // namespace AST