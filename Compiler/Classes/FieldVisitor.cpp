#include "FieldVisitor.h"

void FieldVisitor::Visit(const AST::ExpressionAdd&) {};

void FieldVisitor::Visit(const AST::ExpressionSub&) {};

void FieldVisitor::Visit(const AST::ExpressionMul&) {};

void FieldVisitor::Visit(const AST::ExpressionDiv&) {};

void FieldVisitor::Visit(const AST::ExpressionAnd&) {};

void FieldVisitor::Visit(const AST::ExpressionOr&) {};

void FieldVisitor::Visit(const AST::ExpressionEqual&) {};

void FieldVisitor::Visit(const AST::ExpressionMod&) {};

void FieldVisitor::Visit(const AST::ExpressionLess&) {};

void FieldVisitor::Visit(const AST::ExpressionGreater&) {};

void FieldVisitor::Visit(const AST::ExpressionFalse&) {};

void FieldVisitor::Visit(const AST::ExpressionTrue&) {};

void FieldVisitor::Visit(const AST::ExpressionArrayElement&) {};

void FieldVisitor::Visit(const AST::ExpressionLength&) {};

void FieldVisitor::Visit(const AST::ExpressionNewVariable&) {};

void FieldVisitor::Visit(const AST::ExpressionNewArray&) {};

void FieldVisitor::Visit(const AST::ExpressionNot&) {};

void FieldVisitor::Visit(const AST::ExpressionBraces&) {};

void FieldVisitor::Visit(const AST::ExpressionVariable&) {};

void FieldVisitor::Visit(const AST::ExpressionThis&) {};

void FieldVisitor::Visit(const AST::ExpressionMethodInvocation&) {};

void FieldVisitor::Visit(const AST::FunctionArguments&) {};

void FieldVisitor::Visit(const AST::Program&) {};

void FieldVisitor::Visit(const AST::ClassDeclarationList&) {};

void FieldVisitor::Visit(const AST::ClassDeclarationSimple&) {};

void FieldVisitor::Visit(const AST::ClassDeclarationInheritted&) {};

void FieldVisitor::Visit(const AST::DeclarationList&) {};

void FieldVisitor::Visit(const AST::DeclarationVariable& decl) {
  decl.GetDeclaration()->Accept(*this);
};

void FieldVisitor::Visit(const AST::DeclarationMethod& decl) {
  var_ = nullptr;
};

void FieldVisitor::Visit(const AST::VariableDeclaration& var) {
  var_ = &var;
};

void FieldVisitor::Visit(const AST::MethodDeclaration&) {};

void FieldVisitor::Visit(const AST::Formals&) {};

void FieldVisitor::Visit(const AST::MainClass&) {};

void FieldVisitor::Visit(const AST::StatementAssert&) {};

void FieldVisitor::Visit(const AST::StatementVariableDeclaration&) {};

void FieldVisitor::Visit(const AST::StatementNewScope&) {};

void FieldVisitor::Visit(const AST::StatementIfReduced&) {};

void FieldVisitor::Visit(const AST::StatementIfFull&) {};

void FieldVisitor::Visit(const AST::StatementWhile&) {};

void FieldVisitor::Visit(const AST::StatementPrint&) {};

void FieldVisitor::Visit(const AST::StatementAssignment&) {};

void FieldVisitor::Visit(const AST::StatementReturn&) {};

void FieldVisitor::Visit(const AST::StatementMethodInvocation&) {};

void FieldVisitor::Visit(const AST::LValueSimple&) {};

void FieldVisitor::Visit(const AST::LValueArrayElement&) {};

void FieldVisitor::Visit(const AST::MethodInvocation&) {};

void FieldVisitor::Visit(const AST::StatementList&) {};

void FieldVisitor::Visit(const AST::ExpressionNumber&) {};

void FieldVisitor::Visit(const AST::ArrayElementLValue&){};

void FieldVisitor::Visit(const AST::SimpleLValue&) {}

const AST::VariableDeclaration *FieldVisitor::GetVariable(const AST::Declaration &decl) {
  FieldVisitor visitor;
  decl.Accept(visitor);
  return visitor.var_;
};
