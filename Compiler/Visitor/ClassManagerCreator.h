#pragma once

#include "Visitor.h"
#include "ClassManager.h"

namespace AST {

class ClassManagerCreator : public Visitor {
 public:
  static ClassManager MakeClassManager(Program &);

  void Visit(const ExpressionAdd &);
  void Visit(const ExpressionSub &);
  void Visit(const ExpressionMul &);
  void Visit(const ExpressionDiv &);
  void Visit(const ExpressionAnd &);
  void Visit(const ExpressionOr &);
  void Visit(const ExpressionEqual &);
  void Visit(const ExpressionMod &);
  void Visit(const ExpressionLess &);
  void Visit(const ExpressionGreater &);
  void Visit(const ExpressionFalse &);
  void Visit(const ExpressionTrue &);
  void Visit(const ExpressionArrayElement &);
  void Visit(const ExpressionLength &);
  void Visit(const ExpressionNewVariable &);
  void Visit(const ExpressionNewArray &);
  void Visit(const ExpressionNot &);
  void Visit(const ExpressionBraces &);
  void Visit(const ExpressionVariable &);
  void Visit(const ExpressionThis &);
  void Visit(const ExpressionMethodInvocation &);
  void Visit(const FunctionArguments &);
  void Visit(const Program &);
  void Visit(const ClassDeclarationList &);
  void Visit(const ClassDeclarationSimple &);
  void Visit(const ClassDeclarationInheritted &);
  void Visit(const DeclarationList &);
  void Visit(const DeclarationVariable &);
  void Visit(const DeclarationMethod &);
  void Visit(const VariableDeclaration &);
  void Visit(const MethodDeclaration &);
  void Visit(const Formals &);
  void Visit(const MainClass &);
  void Visit(const StatementAssert &);
  void Visit(const StatementVariableDeclaration &);
  void Visit(const StatementNewScope &);
  void Visit(const StatementIfReduced &);
  void Visit(const StatementIfFull &);
  void Visit(const StatementWhile &);
  void Visit(const StatementPrint &);
  void Visit(const StatementAssignment &);
  void Visit(const StatementReturn &);
  void Visit(const StatementMethodInvocation &);
  void Visit(const LValueSimple &);
  void Visit(const LValueArrayElement &);
  void Visit(const MethodInvocation &);
  void Visit(const StatementList &);
  void Visit(const ExpressionNumber &);
  void Visit(const ArrayElementLValue &);
  void Visit(const Type &);
  void Visit(const SimpleLValue &);

 private:
  ClassManagerCreator() = default;

 private:
  ClassManager manager_;
};

} // namespace AST
