#include "TypeGetter.h"

std::string TypeGetter::GetType(const AST::Expression &expr,
                                const SymbolTable &table,
                                const FunctionManager &manager,
                                const ClassManager &cl) {
  TypeGetter getter(table, manager, cl);
  expr.Accept(getter);
  return std::move(getter.type_);
}

TypeGetter::TypeGetter(const SymbolTable &table,
                       const FunctionManager &function_manager,
                       const ClassManager &class_manager)
    : table_(table), function_manager_(function_manager), class_manager_(class_manager) {}

void TypeGetter::Visit(const AST::ExpressionAdd &) {
  type_ = "int";
}

void TypeGetter::Visit(const AST::ExpressionSub &) {
  type_ = "int";
}

void TypeGetter::Visit(const AST::ExpressionMul &) {
  type_ = "int";
}

void TypeGetter::Visit(const AST::ExpressionDiv &) {
  type_ = "int";
}

void TypeGetter::Visit(const AST::ExpressionAnd &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionOr &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionEqual &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionMod &) {
  type_ = "int";
}

void TypeGetter::Visit(const AST::ExpressionLess &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionGreater &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionFalse &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionTrue &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionArrayElement &elem) {
  elem.GetArray()->Accept(*this);
}

void TypeGetter::Visit(const AST::ExpressionLength &) {}

void TypeGetter::Visit(const AST::ExpressionNewVariable &var) {
  type_ = var.GetTypeName();
}

void TypeGetter::Visit(const AST::ExpressionNewArray &) {}

void TypeGetter::Visit(const AST::ExpressionNot &) {
  type_ = "boolean";
}

void TypeGetter::Visit(const AST::ExpressionBraces &expr) {
  expr.GetInnerExpression()->Accept(*this);
}

void TypeGetter::Visit(const AST::ExpressionVariable &var) {
  if (!table_.HasVariable(var.GetVariableName())) {
    auto cl = table_.GetVariableType("this");
    type_ = class_manager_.GetClass(cl).GetFieldType(var.GetVariableName());
  } else {
    type_ = table_.GetVariableType(var.GetVariableName());
  }
}

void TypeGetter::Visit(const AST::ExpressionThis &) {
  type_ = table_.GetVariableType("this");
}

void TypeGetter::Visit(const AST::ExpressionMethodInvocation &invoc) {
  invoc.GetMethod()->Accept(*this);
}

void TypeGetter::Visit(const AST::FunctionArguments &args) {}

void TypeGetter::Visit(const AST::Program &) {}

void TypeGetter::Visit(const AST::ClassDeclarationList &) {}

void TypeGetter::Visit(const AST::ClassDeclarationSimple &) {}

void TypeGetter::Visit(const AST::ClassDeclarationInheritted &) {}

void TypeGetter::Visit(const AST::DeclarationList &) {}

void TypeGetter::Visit(const AST::DeclarationVariable &) {}

void TypeGetter::Visit(const AST::DeclarationMethod &) {}

void TypeGetter::Visit(const AST::VariableDeclaration &) {}

void TypeGetter::Visit(const AST::MethodDeclaration &) {}

void TypeGetter::Visit(const AST::Formals &) {}

void TypeGetter::Visit(const AST::MainClass &) {}

void TypeGetter::Visit(const AST::StatementAssert &) {}

void TypeGetter::Visit(const AST::StatementVariableDeclaration &) {}

void TypeGetter::Visit(const AST::StatementNewScope &) {}

void TypeGetter::Visit(const AST::StatementIfReduced &) {}

void TypeGetter::Visit(const AST::StatementIfFull &) {}

void TypeGetter::Visit(const AST::StatementWhile &) {}

void TypeGetter::Visit(const AST::StatementPrint &) {}

void TypeGetter::Visit(const AST::StatementAssignment &) {}

void TypeGetter::Visit(const AST::StatementReturn &) {}

void TypeGetter::Visit(const AST::StatementMethodInvocation &) {}

void TypeGetter::Visit(const AST::LValueSimple &) {}

void TypeGetter::Visit(const AST::LValueArrayElement &lv) {
  lv.GetLvalue()->Accept(*this);
}

void TypeGetter::Visit(const AST::MethodInvocation &invoc) {
  invoc.GetObject()->Accept(*this);
  type_ = function_manager_.GetFunction(type_, invoc.GetMethodName()).GetReturningType();
}

void TypeGetter::Visit(const AST::StatementList &) {}

void TypeGetter::Visit(const AST::ExpressionNumber &) {
  type_ = "int";
}

void TypeGetter::Visit(const AST::ArrayElementLValue &lv) {
  lv.GetArray()->Accept(*this);
//  delete last []
  type_.pop_back();
  type_.pop_back();
}

void TypeGetter::Visit(const AST::SimpleLValue &) {}

void TypeGetter::Visit(const AST::Type &) {}

