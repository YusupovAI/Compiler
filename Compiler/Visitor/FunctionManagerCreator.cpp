#include "FunctionManagerCreator.h"

namespace AST {

class FunctionManager FunctionManagerCreator::MakeFunctionManager(class AST::Program & p) {
  FunctionManagerCreator creator;
  p.Accept(creator);
  return std::move(creator.manager_);
}

void FunctionManagerCreator::Visit(const ExpressionAdd&) {}

void FunctionManagerCreator::Visit(const ExpressionSub&) {}

void FunctionManagerCreator::Visit(const ExpressionMul&) {}

void FunctionManagerCreator::Visit(const ExpressionDiv&) {}

void FunctionManagerCreator::Visit(const ExpressionAnd&) {}

void FunctionManagerCreator::Visit(const ExpressionOr&) {}

void FunctionManagerCreator::Visit(const ExpressionEqual&) {}

void FunctionManagerCreator::Visit(const ExpressionMod&) {}

void FunctionManagerCreator::Visit(const ExpressionLess&) {}

void FunctionManagerCreator::Visit(const ExpressionGreater&) {}

void FunctionManagerCreator::Visit(const ExpressionFalse&) {}

void FunctionManagerCreator::Visit(const ExpressionTrue&) {}

void FunctionManagerCreator::Visit(const ExpressionArrayElement&) {}

void FunctionManagerCreator::Visit(const ExpressionLength&) {}

void FunctionManagerCreator::Visit(const ExpressionNewVariable&) {}

void FunctionManagerCreator::Visit(const ExpressionNewArray&) {}

void FunctionManagerCreator::Visit(const ExpressionNot&) {}

void FunctionManagerCreator::Visit(const ExpressionBraces&) {}

void FunctionManagerCreator::Visit(const ExpressionVariable&) {}

void FunctionManagerCreator::Visit(const ExpressionThis&) {}

void FunctionManagerCreator::Visit(const ExpressionMethodInvocation&) {}

void FunctionManagerCreator::Visit(const FunctionArguments&) {}

void FunctionManagerCreator::Visit(const Program& p) {
  p.GetClassesDeclaration()->Accept(*this);
}

void FunctionManagerCreator::Visit(const ClassDeclarationList& decl) {
  if (decl.GetHead() == nullptr) {
    return;
  }
  decl.GetHead()->Accept(*this);
  decl.GetTail()->Accept(*this);
}

void FunctionManagerCreator::Visit(const ClassDeclarationSimple& decl) {
  class_name_ = decl.GetClassName();
  decl.GetDeclarations()->Accept(*this);
}

void FunctionManagerCreator::Visit(const ClassDeclarationInheritted&) {}

void FunctionManagerCreator::Visit(const DeclarationList& list) {
  if (list.GetHead() == nullptr) {
    return;
  }
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void FunctionManagerCreator::Visit(const DeclarationVariable&) {}

void FunctionManagerCreator::Visit(const DeclarationMethod& decl) {
  decl.GetDeclaration()->Accept(*this);
}

void FunctionManagerCreator::Visit(const VariableDeclaration&) {}

void FunctionManagerCreator::Visit(const MethodDeclaration& method) {
  manager_.AddFunction(class_name_, method.GetMethodName(), method);
}

void FunctionManagerCreator::Visit(const Formals&) {}

void FunctionManagerCreator::Visit(const MainClass&) {}

void FunctionManagerCreator::Visit(const StatementAssert&) {}

void FunctionManagerCreator::Visit(const StatementVariableDeclaration&) {}

void FunctionManagerCreator::Visit(const StatementNewScope&) {}

void FunctionManagerCreator::Visit(const StatementIfReduced&) {}

void FunctionManagerCreator::Visit(const StatementIfFull&) {}

void FunctionManagerCreator::Visit(const StatementWhile&) {}

void FunctionManagerCreator::Visit(const StatementPrint&) {}

void FunctionManagerCreator::Visit(const StatementAssignment&) {}

void FunctionManagerCreator::Visit(const StatementReturn&) {}

void FunctionManagerCreator::Visit(const StatementMethodInvocation&) {}

void FunctionManagerCreator::Visit(const LValueSimple&) {}

void FunctionManagerCreator::Visit(const LValueArrayElement&) {}

void FunctionManagerCreator::Visit(const MethodInvocation&) {}

void FunctionManagerCreator::Visit(const StatementList&) {}

void FunctionManagerCreator::Visit(const ExpressionNumber&) {}

void FunctionManagerCreator::Visit(const ArrayElementLValue&) {}

void FunctionManagerCreator::Visit(const Type&) {}

void FunctionManagerCreator::Visit(const SimpleLValue&) {}

}
