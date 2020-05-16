#include "ClassManagerCreator.h"

namespace AST {

ClassManager ClassManagerCreator::MakeClassManager(Program &program) {
  ClassManagerCreator creator;
  program.Accept(creator);
  return std::move(creator.manager_);
}

void ClassManagerCreator::Visit(const ExpressionAdd &) {}

void ClassManagerCreator::Visit(const ExpressionSub &) {}

void ClassManagerCreator::Visit(const ExpressionMul &) {}

void ClassManagerCreator::Visit(const ExpressionDiv &) {}

void ClassManagerCreator::Visit(const ExpressionAnd &) {}

void ClassManagerCreator::Visit(const ExpressionOr &) {}

void ClassManagerCreator::Visit(const ExpressionEqual &) {}

void ClassManagerCreator::Visit(const ExpressionMod &) {}

void ClassManagerCreator::Visit(const ExpressionLess &) {}

void ClassManagerCreator::Visit(const ExpressionGreater &) {}

void ClassManagerCreator::Visit(const ExpressionFalse &) {}

void ClassManagerCreator::Visit(const ExpressionTrue &) {}

void ClassManagerCreator::Visit(const ExpressionArrayElement &) {}

void ClassManagerCreator::Visit(const ExpressionLength &) {}

void ClassManagerCreator::Visit(const ExpressionNewVariable &) {}

void ClassManagerCreator::Visit(const ExpressionNewArray &) {}

void ClassManagerCreator::Visit(const ExpressionNot &) {}

void ClassManagerCreator::Visit(const ExpressionBraces &) {}

void ClassManagerCreator::Visit(const ExpressionVariable &) {}

void ClassManagerCreator::Visit(const ExpressionThis &) {}

void ClassManagerCreator::Visit(const ExpressionMethodInvocation &) {}

void ClassManagerCreator::Visit(const FunctionArguments &) {}

void ClassManagerCreator::Visit(const Program &program) {
  program.GetClassesDeclaration()->Accept(*this);
}

void ClassManagerCreator::Visit(const ClassDeclarationList &list) {
  if (list.GetHead() == nullptr) {
    return;
  }
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void ClassManagerCreator::Visit(const ClassDeclarationSimple &decl) {
  manager_.AddClass(decl.GetClassName());
}

void ClassManagerCreator::Visit(const ClassDeclarationInheritted &) {}

void ClassManagerCreator::Visit(const DeclarationList &) {}

void ClassManagerCreator::Visit(const DeclarationVariable &) {}

void ClassManagerCreator::Visit(const DeclarationMethod &) {}

void ClassManagerCreator::Visit(const VariableDeclaration &) {}

void ClassManagerCreator::Visit(const MethodDeclaration &) {}

void ClassManagerCreator::Visit(const Formals &) {}

void ClassManagerCreator::Visit(const MainClass &) {}

void ClassManagerCreator::Visit(const StatementAssert &) {}

void ClassManagerCreator::Visit(const StatementVariableDeclaration &) {}

void ClassManagerCreator::Visit(const StatementNewScope &) {}

void ClassManagerCreator::Visit(const StatementIfReduced &) {}

void ClassManagerCreator::Visit(const StatementIfFull &) {}

void ClassManagerCreator::Visit(const StatementWhile &) {}

void ClassManagerCreator::Visit(const StatementPrint &) {}

void ClassManagerCreator::Visit(const StatementAssignment &) {}

void ClassManagerCreator::Visit(const StatementReturn &) {}

void ClassManagerCreator::Visit(const StatementMethodInvocation &) {}

void ClassManagerCreator::Visit(const LValueSimple &) {}

void ClassManagerCreator::Visit(const LValueArrayElement &) {}

void ClassManagerCreator::Visit(const MethodInvocation &) {}

void ClassManagerCreator::Visit(const StatementList &) {}

void ClassManagerCreator::Visit(const ExpressionNumber &) {}

void ClassManagerCreator::Visit(const ArrayElementLValue &) {}

void ClassManagerCreator::Visit(const Type &) {}

void ClassManagerCreator::Visit(const SimpleLValue &) {}

}