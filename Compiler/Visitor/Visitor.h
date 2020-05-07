#pragma once

#include "include_list.h"


namespace AST {

class Visitor {
 public:
  virtual void Visit(const ExpressionAdd&) = 0;
  virtual void Visit(const ExpressionSub&) = 0;
  virtual void Visit(const ExpressionMul&) = 0;
  virtual void Visit(const ExpressionDiv&) = 0;
  virtual void Visit(const ExpressionAnd&) = 0;
  virtual void Visit(const ExpressionOr&) = 0;
  virtual void Visit(const ExpressionEqual&) = 0;
  virtual void Visit(const ExpressionMod&) = 0;
  virtual void Visit(const ExpressionLess&) = 0;
  virtual void Visit(const ExpressionGreater&) = 0;
  virtual void Visit(const ExpressionFalse&) = 0;
  virtual void Visit(const ExpressionTrue&) = 0;
  virtual void Visit(const ExpressionArrayElement&) = 0;
  virtual void Visit(const ExpressionLength&) = 0;
  virtual void Visit(const ExpressionNewVariable&) = 0;
  virtual void Visit(const ExpressionNewArray&) = 0;
  virtual void Visit(const ExpressionNot&) = 0;
  virtual void Visit(const ExpressionBraces&) = 0;
  virtual void Visit(const ExpressionVariable&) = 0;
  virtual void Visit(const ExpressionThis&) = 0;
  virtual void Visit(const ExpressionMethodInvocation&) = 0;
  virtual void Visit(const FunctionArguments&) = 0;
  virtual void Visit(const Program&) = 0;
  virtual void Visit(const ClassDeclarationList&) = 0;
  virtual void Visit(const ClassDeclarationSimple&) = 0;
  virtual void Visit(const ClassDeclarationInheritted&) = 0;
  virtual void Visit(const DeclarationList&) = 0;
  virtual void Visit(const DeclarationVariable&) = 0;
  virtual void Visit(const DeclarationMethod&) = 0;
  virtual void Visit(const VariableDeclaration&) = 0;
  virtual void Visit(const MethodDeclaration&) = 0;
  virtual void Visit(const TypeSimple&) = 0;
  virtual void Visit(const TypeArray&) = 0;
  virtual void Visit(const ArrayType&) = 0;
  virtual void Visit(const Formals&) = 0;
  virtual void Visit(const MainClass&) = 0;
  virtual void Visit(const StatementAssert&) = 0;
  virtual void Visit(const StatementVariableDeclaration&) = 0;
  virtual void Visit(const StatementNewScope&) = 0;
  virtual void Visit(const StatementIfReduced&) = 0;
  virtual void Visit(const StatementIfFull&) = 0;
  virtual void Visit(const StatementWhile&) = 0;
  virtual void Visit(const StatementPrint&) = 0;
  virtual void Visit(const StatementAssignment&) = 0;
  virtual void Visit(const StatementReturn&) = 0;
  virtual void Visit(const StatementMethodInvocation&) = 0;
  virtual void Visit(const LValueSimple&) = 0;
  virtual void Visit(const LValueArrayElement&) = 0;
  virtual void Visit(const MethodInvocation&) = 0;
  virtual void Visit(const StatementList&) = 0;
  virtual void Visit(const ExpressionNumber&) = 0;
  virtual void Visit(const SimpleType&) = 0;
  virtual void Visit(const ArrayElementLValue&) =0;
  virtual void Visit(const SimpleLValue&) = 0;

  virtual ~Visitor(){};
};

}  // namespace AST