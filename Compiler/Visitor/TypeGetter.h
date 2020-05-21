#pragma once

#include "Visitor.h"

#include "SymbolTable.h"
#include "FunctionManager.h"

#include <string>
#include "ClassManager.h"

class TypeGetter : public AST::Visitor {
 public:
  static std::string GetType(const AST::Expression &expr,
                             const SymbolTable &,
                             const FunctionManager &,
                             const ClassManager &);

  void Visit(const AST::ExpressionAdd &) override;
  void Visit(const AST::ExpressionSub &) override;
  void Visit(const AST::ExpressionMul &) override;
  void Visit(const AST::ExpressionDiv &) override;
  void Visit(const AST::ExpressionAnd &) override;
  void Visit(const AST::ExpressionOr &) override;
  void Visit(const AST::ExpressionEqual &) override;
  void Visit(const AST::ExpressionMod &) override;
  void Visit(const AST::ExpressionLess &) override;
  void Visit(const AST::ExpressionGreater &) override;
  void Visit(const AST::ExpressionFalse &) override;
  void Visit(const AST::ExpressionTrue &) override;
  void Visit(const AST::ExpressionArrayElement &) override;
  void Visit(const AST::ExpressionLength &) override;
  void Visit(const AST::ExpressionNewVariable &) override;
  void Visit(const AST::ExpressionNewArray &) override;
  void Visit(const AST::ExpressionNot &) override;
  void Visit(const AST::ExpressionBraces &) override;
  void Visit(const AST::ExpressionVariable &) override;
  void Visit(const AST::ExpressionThis &) override;
  void Visit(const AST::ExpressionMethodInvocation &) override;
  void Visit(const AST::FunctionArguments &) override;
  void Visit(const AST::Program &) override;
  void Visit(const AST::ClassDeclarationList &) override;
  void Visit(const AST::ClassDeclarationSimple &) override;
  void Visit(const AST::ClassDeclarationInheritted &) override;
  void Visit(const AST::DeclarationList &) override;
  void Visit(const AST::DeclarationVariable &) override;
  void Visit(const AST::DeclarationMethod &) override;
  void Visit(const AST::VariableDeclaration &) override;
  void Visit(const AST::MethodDeclaration &) override;
  void Visit(const AST::Formals &) override;
  void Visit(const AST::MainClass &) override;
  void Visit(const AST::StatementAssert &) override;
  void Visit(const AST::StatementVariableDeclaration &) override;
  void Visit(const AST::StatementNewScope &) override;
  void Visit(const AST::StatementIfReduced &) override;
  void Visit(const AST::StatementIfFull &) override;
  void Visit(const AST::StatementWhile &) override;
  void Visit(const AST::StatementPrint &) override;
  void Visit(const AST::StatementAssignment &) override;
  void Visit(const AST::StatementReturn &) override;
  void Visit(const AST::StatementMethodInvocation &) override;
  void Visit(const AST::LValueSimple &) override;
  void Visit(const AST::LValueArrayElement &) override;
  void Visit(const AST::MethodInvocation &) override;
  void Visit(const AST::StatementList &) override;
  void Visit(const AST::ExpressionNumber &) override;
  void Visit(const AST::ArrayElementLValue &) override;
  void Visit(const AST::SimpleLValue &) override;
  void Visit(const AST::Type &) override;

 private:
  TypeGetter(const SymbolTable &table, const FunctionManager &manager, const ClassManager &);

 private:
  std::string type_;
  const SymbolTable &table_;
  const FunctionManager &function_manager_;
  const ClassManager &class_manager_;
};
