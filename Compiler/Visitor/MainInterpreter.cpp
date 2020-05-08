#include "ScopeLayer.h"
#include "IntegerValue.h"
#include "Object.h"
#include "MainInterpreter.h"
#include "BooleanValue.h"
#include "TypeGetter.h"


namespace AST {

static int GetInteger(Object& obj) {
  if (obj.GetType() != "int") {
    throw std::logic_error("Value expected to be an integer but it is not");
  }
  return std::dynamic_pointer_cast<IntegerValue>(obj.GetValue())->GetValue();
}

static Object MakeInteger(int x) {
  Object obj("int");
  obj.SetValue(std::make_unique<IntegerValue>(x));
  return obj;
}

static int GetBoolean(Object& obj) {
  if (obj.GetType() != "boolean") {
    throw std::logic_error("Value expected to be an boolean but it is not");
  }
  return std::dynamic_pointer_cast<BooleanValue>(obj.GetValue())->GetValue();
}

static Object MakeBoolean(bool x) {
  Object obj("boolean");
  obj.SetValue(std::make_unique<BooleanValue>(x));
  return obj;
}

static std::string GetType(const TreeNode& node) {
  TypeGetter getter;
  node.Accept(getter);
  return getter.GetType();
}

MainInterpreter::MainInterpreter(std::ostream& out) : out_(out){}

void MainInterpreter::Visit(const ExpressionAdd& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeInteger(GetInteger(tos_value_) + tmp);
}

void MainInterpreter::Visit(const ExpressionSub& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeInteger(GetInteger(tos_value_) - tmp);
}

void MainInterpreter::Visit(const ExpressionMul& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeInteger(GetInteger(tos_value_) * tmp);
}

void MainInterpreter::Visit(const ExpressionDiv& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeInteger(GetInteger(tos_value_) / tmp);
}

void MainInterpreter::Visit(const ExpressionAnd& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetBoolean(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeBoolean(GetBoolean(tos_value_) && tmp);
}

void MainInterpreter::Visit(const ExpressionOr& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetBoolean(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeBoolean(GetBoolean(tos_value_) || tmp);
}

void MainInterpreter::Visit(const ExpressionEqual& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeBoolean(GetInteger(tos_value_) == tmp);
}

void MainInterpreter::Visit(const ExpressionMod& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeInteger(GetInteger(tos_value_) % tmp);
}

void MainInterpreter::Visit(const ExpressionLess& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeBoolean(GetInteger(tos_value_) < tmp);
}

void MainInterpreter::Visit(const ExpressionGreater& exp) {
  exp.GetRight()->Accept(*this);
  int tmp = GetInteger(tos_value_);
  exp.GetLeft()->Accept(*this);
  tos_value_ = MakeBoolean(GetInteger(tos_value_) > tmp);
}

void MainInterpreter::Visit(const ExpressionFalse& exp) {
  tos_value_ = MakeBoolean(false);
}

void MainInterpreter::Visit(const ExpressionTrue& exp) {
  tos_value_ = MakeBoolean(true);
}

void MainInterpreter::Visit(const ExpressionArrayElement& exp) {
  throw std::runtime_error("Unexpected array indexing\n");
}

void MainInterpreter::Visit(const ExpressionLength& exp) {
  throw std::runtime_error("Unexpected length\n");
}

void MainInterpreter::Visit(const ExpressionNewVariable& exp) {
  throw std::runtime_error("Only primitive types are allowed");
}

void MainInterpreter::Visit(const ExpressionNewArray& exp) {
  throw std::runtime_error("No arrays are allowed");
}

void MainInterpreter::Visit(const ExpressionNot& exp) {
  exp.GetBoolExpression()->Accept(*this);
  tos_value_ = MakeBoolean(!GetBoolean(tos_value_));
}

void MainInterpreter::Visit(const ExpressionBraces& exp) {
  exp.GetInnerExpression()->Accept(*this);
}

void MainInterpreter::Visit(const ExpressionVariable& exp) {
  tos_value_ = layers_.back().GetValue(exp.GetVariableName());
}

void MainInterpreter::Visit(const ExpressionThis& exp) {
  throw std::runtime_error("No this is allowed");
}

void MainInterpreter::Visit(const ExpressionMethodInvocation& exp) {
  throw std::runtime_error("No methods are allowed");
}

void MainInterpreter::Visit(const FunctionArguments&) {
  throw std::runtime_error("No function is allowed");
}

void MainInterpreter::Visit(const Program& program) {
  program.GetMainClass()->Accept(*this);
}

void MainInterpreter::Visit(const ClassDeclarationList& decl) {}

void MainInterpreter::Visit(const ClassDeclarationSimple&) {}

void MainInterpreter::Visit(const ClassDeclarationInheritted&) {}

void MainInterpreter::Visit(const DeclarationList&) {}

void MainInterpreter::Visit(const DeclarationVariable& decl) {
  decl.GetDeclaration()->Accept(*this);
}

void MainInterpreter::Visit(const DeclarationMethod& decl) {

}

void MainInterpreter::Visit(const VariableDeclaration& decl) {
  layers_.back().DeclareVariable(decl.GetVariableName(), GetType(*decl.GetVariableType()));
}

void MainInterpreter::Visit(const MethodDeclaration& decl) {}

void MainInterpreter::Visit(const TypeSimple&) {
}

void MainInterpreter::Visit(const TypeArray&) {
  throw std::runtime_error("No arrays are allowed");
}

void MainInterpreter::Visit(const ArrayType&) {
  
}

void MainInterpreter::Visit(const Formals&) {}

void MainInterpreter::Visit(const MainClass& cls) {
  layers_.emplace_back();
  cls.GetStatements()->Accept(*this);
}

void MainInterpreter::Visit(const StatementAssert& asrt) {
  asrt.GetInnerExpression()->Accept(*this);
  if (!GetBoolean(tos_value_)) {
    throw std::logic_error("Assertion handled");
  }
}

void MainInterpreter::Visit(const StatementVariableDeclaration& decl) {
  decl.GetDeclaration()->Accept(*this);
}

void MainInterpreter::Visit(const StatementNewScope& scope) {
  layers_.emplace_back(&layers_.back());
  scope.GetStatements()->Accept(*this);
  layers_.pop_back();
}

void MainInterpreter::Visit(const StatementIfReduced& stmt) {
  stmt.GetCondition()->Accept(*this);
  if (GetBoolean(tos_value_)) {
    stmt.GetBody()->Accept(*this);
  }
}

void MainInterpreter::Visit(const StatementIfFull& stmt) {
  stmt.GetCondition()->Accept(*this);
  if (GetBoolean(tos_value_)) {
    stmt.GetTrueBody()->Accept(*this);
  } else {
    stmt.GetFlaseBody()->Accept(*this);
  }
}

void MainInterpreter::Visit(const StatementWhile& stmt) {
  while (true) {
    stmt.GetCondition()->Accept(*this);
    if (!GetBoolean(tos_value_)) {
      break;
    }
    stmt.GetBody()->Accept(*this);
  }
}

void MainInterpreter::Visit(const StatementPrint& print) {
  print.GetInnerExpression()->Accept(*this);
  out_ << GetInteger(tos_value_) << '\n';
}

void MainInterpreter::Visit(const StatementAssignment& stmt) {
  stmt.GetRhs()->Accept(*this);
  stmt.GetLhs()->Accept(*this);
}

void MainInterpreter::Visit(const StatementReturn& ret) {
  ret.GetInnerExpression()->Accept(*this);
  returned_ = true;
}

void MainInterpreter::Visit(const StatementMethodInvocation&) {}
void MainInterpreter::Visit(const LValueSimple& simple) {
  simple.GetLvalue()->Accept(*this);
};

void MainInterpreter::Visit(const LValueArrayElement&) {
  throw std::runtime_error("Arrays are not allowed");
}

void MainInterpreter::Visit(const MethodInvocation&) {
  throw std::runtime_error("No methods are allowed");
}

void MainInterpreter::Visit(const StatementList& list) {
  if (list.GetHead() == nullptr || returned_) {
    return;
  }
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void MainInterpreter::Visit(const ExpressionNumber& num) {
  tos_value_ = MakeInteger(num.GetValue());
}

void MainInterpreter::Visit(const SimpleType& t) {
  if (t.GetType() != "int" && t.GetType() != "boolean") {
    throw std::runtime_error("Only int and boolean variables are allowed");
  }
}

void MainInterpreter::Visit(const ArrayElementLValue&) {
  throw std::runtime_error("No array is allowed");
}

void MainInterpreter::Visit(const SimpleLValue& lv) {
  layers_.back().SetValue(lv.GetVariableName(), tos_value_);
}

}