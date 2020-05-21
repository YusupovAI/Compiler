#include "TypeChecker.h"

TypeChecker::TypeChecker(const FunctionManager& manager, const ClassManager& cl)
: function_manager_(manager),
scope_(std::make_unique<TypesScopeLayer>()),
class_manager_(cl) {}

void TypeChecker::Visit(const AST::ExpressionAdd &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in + expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in + expression");
  }
  last_type_ = "int";
}

void TypeChecker::Visit(const AST::ExpressionSub &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in - expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in - expression");
  }
  last_type_ = "int";
}

void TypeChecker::Visit(const AST::ExpressionMul &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in * expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in * expression");
  }
  last_type_ = "int";
}

void TypeChecker::Visit(const AST::ExpressionDiv &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in / expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in / expression");
  }
  last_type_ = "int";
}

void TypeChecker::Visit(const AST::ExpressionAnd &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in and expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in and expression");
  }
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionOr &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in or expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in or expression");
  }
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionEqual &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in == expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in == expression");
  }
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionMod &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in % expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in % expression");
  }
  last_type_ = "int";
}

void TypeChecker::Visit(const AST::ExpressionLess &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in < expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in < expression");
  }
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionGreater &expr) {
  expr.GetLeft()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in > expression");
  }
  expr.GetRight()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non integer usage in > expression");
  }
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionFalse &expr) {
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionTrue &expr) {
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionArrayElement &elem) {
  elem.GetIndex()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Array index should be an integer, but it is not");
  }
  elem.GetArray()->Accept(*this);
  if (last_type_.back() != ']') {
    throw std::logic_error("Expected an array, but it is not");
  }
//  delete last []
  last_type_.pop_back();
  last_type_.pop_back();
}

void TypeChecker::Visit(const AST::ExpressionLength &expr) {
  expr.GetLhs()->Accept(*this);
  if (last_type_.back() != ']') {
    throw std::logic_error("Trying to use length field of not an array");
  }
  last_type_ = "int";
}

void TypeChecker::Visit(const AST::ExpressionNewVariable &expr) {
  last_type_ = expr.GetTypeName();
}

void TypeChecker::Visit(const AST::ExpressionNewArray &arr) {
  arr.GetArraySize()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Array size should be integer");
  }
  last_type_ = arr.GetArrayType()->GetType();
}

void TypeChecker::Visit(const AST::ExpressionNot &expr) {
  expr.GetBoolExpression()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Not boolean usage in not expression");
  }
  last_type_ = "boolean";
}

void TypeChecker::Visit(const AST::ExpressionBraces &expr) {
  expr.GetInnerExpression()->Accept(*this);
}

void TypeChecker::Visit(const AST::ExpressionVariable &var) {
  if (scope_->IsDeclared(var.GetVariableName())) {
    last_type_ = scope_->GetType(var.GetVariableName());
    return;
  }
  if (current_class_.empty()) {
    throw std::logic_error("Usage of undeclared variable " + var.GetVariableName());
  }
  auto& cl = class_manager_.GetClass(current_class_);
  if (!cl.HasField(var.GetVariableName())) {
    throw std::logic_error("Usage of undeclared variable " + var.GetVariableName());
  }
  last_type_ = cl.GetFieldType(var.GetVariableName());
}

void TypeChecker::Visit(const AST::ExpressionThis &expr) {
  last_type_ = current_class_;
}

void TypeChecker::Visit(const AST::ExpressionMethodInvocation &invoc) {
  invoc.GetMethod()->Accept(*this);
}

void TypeChecker::Visit(const AST::FunctionArguments &args) {}

void TypeChecker::Visit(const AST::Program &program) {
  program.GetMainClass()->Accept(*this);
  program.GetClassesDeclaration()->Accept(*this);
}

void TypeChecker::Visit(const AST::ClassDeclarationList &list) {
  if (list.GetHead() == nullptr) {
    return;
  }
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void TypeChecker::Visit(const AST::ClassDeclarationSimple &simple) {
  current_class_ = simple.GetClassName();
  simple.GetDeclarations()->Accept(*this);
}

void TypeChecker::Visit(const AST::ClassDeclarationInheritted &) {}

void TypeChecker::Visit(const AST::DeclarationList &list) {
  if (list.GetHead() == nullptr) {
    return;
  }
  list.GetHead()->Accept(*this);
}

void TypeChecker::Visit(const AST::DeclarationVariable &var) {
  var.GetDeclaration()->Accept(*this);
}

void TypeChecker::Visit(const AST::DeclarationMethod &method) {
  method.GetDeclaration()->Accept(*this);
}

void TypeChecker::Visit(const AST::VariableDeclaration &decl) {
  if (!class_manager_.HasClass(decl.GetVariableType()->GetType())) {
    throw std::logic_error("Usage of incomplete type: " + decl.GetVariableType()->GetType());
  }
  scope_->DeclareVariable(decl.GetVariableName(), decl.GetVariableType()->GetType());
}

void TypeChecker::Visit(const AST::MethodDeclaration &method) {
  scope_ = std::make_unique<TypesScopeLayer>();
  method.GetFormals()->Accept(*this);
  method.GetStatements()->Accept(*this);
}

void TypeChecker::Visit(const AST::Formals &formals) {
  if (formals.GetHeadType() == nullptr) {
    return;
  }
  scope_->DeclareVariable(formals.GetHeadName(), formals.GetHeadType()->GetType());
  formals.GetTail()->Accept(*this);
}

void TypeChecker::Visit(const AST::MainClass &cl) {
  current_class_.clear();
  cl.GetStatements()->Accept(*this);
}

void TypeChecker::Visit(const AST::StatementAssert &stmt) {
  stmt.GetInnerExpression()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in assert");
  }
}

void TypeChecker::Visit(const AST::StatementVariableDeclaration &decl) {
  decl.GetDeclaration()->Accept(*this);
}

void TypeChecker::Visit(const AST::StatementNewScope &new_scope) {
  auto prev_scope = std::move(scope_);
  scope_ = std::make_unique<TypesScopeLayer>(prev_scope.get());
  new_scope.GetStatements()->Accept(*this);
  scope_ = std::move(prev_scope);
}

void TypeChecker::Visit(const AST::StatementIfReduced &stmt) {
  stmt.GetCondition()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in if statement");
  }
  stmt.GetBody()->Accept(*this);
}

void TypeChecker::Visit(const AST::StatementIfFull &stmt) {
  stmt.GetCondition()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in if statement");
  }
  stmt.GetTrueBody()->Accept(*this);
  stmt.GetFalseBody()->Accept(*this);
}

void TypeChecker::Visit(const AST::StatementWhile &stmt) {
  stmt.GetCondition()->Accept(*this);
  if (last_type_ != "boolean") {
    throw std::logic_error("Non boolean usage in if statement");
  }
  stmt.GetBody()->Accept(*this);
}

void TypeChecker::Visit(const AST::StatementPrint &stmt) {
  stmt.GetInnerExpression()->Accept(*this);
  if (last_type_ != "int") {
    throw std::logic_error("Non int usage in print");
  }
}

void TypeChecker::Visit(const AST::StatementAssignment &stmt) {
  stmt.GetRhs()->Accept(*this);
  std::string rhs_type = last_type_;
  stmt.GetLhs()->Accept(*this);
  if (last_type_ != rhs_type) {
    throw std::logic_error("Types mismatch in assignment");
  }
}

void TypeChecker::Visit(const AST::StatementReturn &stmt) {
  stmt.GetInnerExpression()->Accept(*this);
}

void TypeChecker::Visit(const AST::StatementMethodInvocation &stmt) {
  stmt.GetMethod()->Accept(*this);
}

void TypeChecker::Visit(const AST::LValueSimple &) {}

void TypeChecker::Visit(const AST::LValueArrayElement &) {}

void TypeChecker::Visit(const AST::MethodInvocation &invoc) {
  invoc.GetObject()->Accept(*this);
  const Function& func = function_manager_.GetFunction(last_type_, invoc.GetMethodName());
  auto& types = func.GetTypes();
  auto* args = invoc.GetArguments().get();
  for (auto& t:types) {
    if (args->GetHead() == nullptr) {
      throw std::logic_error("Not enough arguments in " + invoc.GetMethodName());
    }
    args->GetHead()->Accept(*this);
    if (last_type_ != t) {
      throw std::logic_error("Type mismatch in " + invoc.GetMethodName());
    }
    args = args->GetTail().get();
  }
  if (args->GetHead() != nullptr) {
    throw std::logic_error("Too many arguments in " + invoc.GetMethodName());
  }
  last_type_ = func.GetReturningType();
}

void TypeChecker::Visit(const AST::StatementList &list) {
  if (list.GetHead() == nullptr) {
    return;
  }
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void TypeChecker::Visit(const AST::ExpressionNumber &num) {
  last_type_ = "int";
}

void TypeChecker::Visit(const AST::ArrayElementLValue &) {}

void TypeChecker::Visit(const AST::SimpleLValue &) {}

void TypeChecker::Visit(const AST::Type &) {}
