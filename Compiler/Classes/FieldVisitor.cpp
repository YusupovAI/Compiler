#include "FieldOrMethodVisitor.h"

void Visit(const AST::ExpressionAdd) {};

void Visit(const AST::ExpressionSub&) {};

void Visit(const AST::ExpressionMul&) {};

void Visit(const AST::ExpressionDiv&) {};

void Visit(const AST::ExpressionAnd&) {};

void Visit(const AST::ExpressionOr&) {};

void Visit(const AST::ExpressionEqual&) {};

void Visit(const AST::ExpressionMod&) {};

void Visit(const AST::ExpressionLess&) {};

void Visit(const AST::ExpressionGreater&) {};

void Visit(const AST::ExpressionFalse&) {};

void Visit(const AST::ExpressionTrue&) {};

void Visit(const AST::ExpressionArrayElement&) {};

void Visit(const AST::ExpressionLength&) {};

void Visit(const AST::ExpressionNewVariable&) {};

void Visit(const AST::ExpressionNewArray&) {};

void Visit(const AST::ExpressionNot&) {};

void Visit(const AST::ExpressionBraces&) {};

void Visit(const AST::ExpressionVariable&) {};

void Visit(const AST::ExpressionThis&) {};

void Visit(const AST::ExpressionMethodInvocation&) {};

void Visit(const AST::FunctionArguments&) {};

void Visit(const AST::Program&) {};

void Visit(const AST::ClassDeclarationList&) {};

void Visit(const AST::ClassDeclarationSimple&) {};

void Visit(const AST::ClassDeclarationInheritted&) {};

void Visit(const AST::DeclarationList&) {};

void Visit(const AST::DeclarationVariable&) {};

void Visit(const AST::DeclarationMethod&) {};

void Visit(const AST::VariableDeclaration&) {};

void Visit(const AST::MethodDeclaration&) {};

void Visit(const AST::Formals&) {};

void Visit(const AST::MainClass&) {};

void Visit(const AST::StatementAssert&) {};

void Visit(const AST::StatementVariableDeclaration&) {};

void Visit(const AST::StatementNewScope&) {};

void Visit(const AST::StatementIfReduced&) {};

void Visit(const AST::StatementIfFull&) {};

void Visit(const AST::StatementWhile&) {};

void Visit(const AST::StatementPrint&) {};

void Visit(const AST::StatementAssignment&) {};

void Visit(const AST::StatementReturn&) {};

void Visit(const AST::StatementMethodInvocation&) {};

void Visit(const AST::LValueSimple&) {};

void Visit(const AST::LValueArrayElement&) {};

void Visit(const AST::MethodInvocation&) {};

void Visit(const AST::StatementList&) {};

void Visit(const AST::ExpressionNumber&) {};

void Visit(const AST::ArrayElementLValue&){};

void Visit(const AST::SimpleLValue&) {};



