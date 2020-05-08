//
// Created by iusupov on 08.05.2020.
//

#include "TypeGetter.h"

namespace AST {

void TypeGetter::Visit(const ExpressionAdd &) {}

void TypeGetter::Visit(const ExpressionSub &) {}

void TypeGetter::Visit(const ExpressionMul &) {}

void TypeGetter::Visit(const ExpressionDiv &) {}

void TypeGetter::Visit(const ExpressionAnd &) {}

void TypeGetter::Visit(const ExpressionOr &) {}

void TypeGetter::Visit(const ExpressionEqual &) {}

void TypeGetter::Visit(const ExpressionMod &) {}

void TypeGetter::Visit(const ExpressionLess &) {}

void TypeGetter::Visit(const ExpressionGreater &) {}

void TypeGetter::Visit(const ExpressionFalse &) {}

void TypeGetter::Visit(const ExpressionTrue &) {}

void TypeGetter::Visit(const ExpressionArrayElement &) {}

void TypeGetter::Visit(const ExpressionLength &) {}

void TypeGetter::Visit(const ExpressionNewVariable &) {}

void TypeGetter::Visit(const ExpressionNewArray &) {}

void TypeGetter::Visit(const ExpressionNot &) {}

void TypeGetter::Visit(const ExpressionBraces &) {}

void TypeGetter::Visit(const ExpressionVariable &) {}

void TypeGetter::Visit(const ExpressionThis &) {}

void TypeGetter::Visit(const ExpressionMethodInvocation &) {}

void TypeGetter::Visit(const FunctionArguments &) {}

void TypeGetter::Visit(const Program &) {}

void TypeGetter::Visit(const ClassDeclarationList &) {}

void TypeGetter::Visit(const ClassDeclarationSimple &) {}

void TypeGetter::Visit(const ClassDeclarationInheritted &) {}

void TypeGetter::Visit(const DeclarationList &) {}

void TypeGetter::Visit(const DeclarationVariable &) {}

void TypeGetter::Visit(const DeclarationMethod &) {}

void TypeGetter::Visit(const VariableDeclaration &) {}

void TypeGetter::Visit(const MethodDeclaration &) {}

void TypeGetter::Visit(const TypeSimple &) {}

void TypeGetter::Visit(const TypeArray &array) {}

void TypeGetter::Visit(const ArrayType &array) {
  array.GetType()->Accept(*this);
  type_ += "[]";
}

void TypeGetter::Visit(const Formals &) {}

void TypeGetter::Visit(const MainClass &) {}

void TypeGetter::Visit(const StatementAssert &) {}

void TypeGetter::Visit(const StatementVariableDeclaration &) {}

void TypeGetter::Visit(const StatementNewScope &) {}

void TypeGetter::Visit(const StatementIfReduced &) {}

void TypeGetter::Visit(const StatementIfFull &) {}

void TypeGetter::Visit(const StatementWhile &) {}

void TypeGetter::Visit(const StatementPrint &) {}

void TypeGetter::Visit(const StatementAssignment &) {}

void TypeGetter::Visit(const StatementReturn &) {}

void TypeGetter::Visit(const StatementMethodInvocation &) {}

void TypeGetter::Visit(const LValueSimple &) {}

void TypeGetter::Visit(const LValueArrayElement &) {}

void TypeGetter::Visit(const MethodInvocation &) {}

void TypeGetter::Visit(const StatementList &) {}

void TypeGetter::Visit(const ExpressionNumber &) {}

void TypeGetter::Visit(const SimpleType &t) {
  type_ = t.GetType();
}

void TypeGetter::Visit(const ArrayElementLValue &) {}

void TypeGetter::Visit(const SimpleLValue &) {}

const std::string &TypeGetter::GetType() const {
  return type_;
}

}
