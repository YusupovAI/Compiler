#include "Interpreter.h"
#include "FunctionManagerCreator.h"
#include "ClassManagerCreator.h"
#include "TypeGetter.h"

namespace AST {

Interpreter::Interpreter(std::ostream &out,
                         const FunctionManager &function_manager,
                         const ClassManager &class_manager)
    : out_(out),
      function_manager_(function_manager),
      class_manager_(class_manager) {}

void Interpreter::Visit(const ExpressionAdd &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left += right;
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionSub &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left -= right;
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionMul &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left *= right;
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionDiv &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left /= right;
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionAnd &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left &= right;
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionOr &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left |= right;
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionEqual &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left = (left == right);
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionMod &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left %= right;
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionLess &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left = (left < right);
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionGreater &exp) {
  exp.GetLeft()->Accept(*this);
  int left = *((int*)table_.GetVariable("#tmp"));
  exp.GetRight()->Accept(*this);
  int right = *((int*)table_.GetVariable("#tmp"));
  left = (left > right);
  table_.Put("#tmp", (char*)&left, 4);
}

void Interpreter::Visit(const ExpressionFalse &exp) {
  int tmp = 0;
  table_.Put("#tmp", (char*)&tmp, 4);
}

void Interpreter::Visit(const ExpressionTrue &exp) {
  int tmp = 1;
  table_.Put("#tmp", (char*)&tmp, 4);
}

void Interpreter::Visit(const ExpressionArrayElement &exp) {
  throw std::runtime_error("Unexpected array indexing\n");
}

void Interpreter::Visit(const ExpressionLength &exp) {
  throw std::runtime_error("Unexpected length\n");
}

void Interpreter::Visit(const ExpressionNewVariable &exp) {}

void Interpreter::Visit(const ExpressionNewArray &exp) {
  throw std::runtime_error("No arrays are allowed");
}

void Interpreter::Visit(const ExpressionNot &exp) {
  int tmp = *((int*)table_.GetVariable("#tmp"));
  table_.Put("#tmp", (char*)&tmp, 4);
}

void Interpreter::Visit(const ExpressionBraces &exp) {
  exp.GetInnerExpression()->Accept(*this);
}

void Interpreter::Visit(const ExpressionVariable &exp) {
  std::string class_name = table_.GetType(exp.GetVariableName());
  if (class_name == "bool") {
    int tmp = *((bool*)table_.GetVariable(exp.GetVariableName()));
    table_.Put("#tmp", (char*)&tmp, 4);
  }
  if (class_name == "int") {
    int tmp = *((int*)table_.GetVariable(exp.GetVariableName()));
    table_.Put("#tmp", (char*)&tmp, 4);
  }
}

void Interpreter::Visit(const ExpressionThis &exp) {}

void Interpreter::Visit(const ExpressionMethodInvocation &exp) {
  exp.GetMethod()->Accept(*this);
}

void Interpreter::Visit(const FunctionArguments &args) {
  function_arguments_.clear();
  const FunctionArguments* cur = &args;
  while (cur->GetHead() != nullptr) {
    std::string type_ = TypeGetter::GetType(*cur->GetHead().get(), table_, function_manager_);
    if (type_ != "int" && type_ != "boolean") {
      cur = cur->GetTail().get();
      continue;
    }
    cur->GetHead()->Accept(*this);
    function_arguments_.push_back(*((int*)table_.GetVariable("#tmp")));
    cur = cur->GetTail().get();
  }
}

void Interpreter::Visit(const Program &program) {
  table_.BeginScope();
  table_.CreateVariable("#tmp", "int", 4);
  program.GetMainClass()->Accept(*this);
  table_.EndScope();
}

void Interpreter::Visit(const ClassDeclarationList &decl) {}

void Interpreter::Visit(const ClassDeclarationSimple &) {}

void Interpreter::Visit(const ClassDeclarationInheritted &) {}

void Interpreter::Visit(const DeclarationList &) {}

void Interpreter::Visit(const DeclarationVariable &decl) {
  decl.GetDeclaration()->Accept(*this);
}

void Interpreter::Visit(const DeclarationMethod &decl) {}

void Interpreter::Visit(const VariableDeclaration &decl) {
  std::string type_ = decl.GetVariableType()->GetType();
  size_t len = 0;
  if (type_ == "boolean") {
    len = 1;
  }
  if (type_ == "int") {
    len = 4;
  }
  table_.CreateVariable(decl.GetVariableName(), decl.GetVariableType()->GetType(), len);
}

void Interpreter::Visit(const MethodDeclaration &decl) {}

void Interpreter::Visit(const Formals &) {}

void Interpreter::Visit(const MainClass &cls) {
  cls.GetStatements()->Accept(*this);
}

void Interpreter::Visit(const StatementAssert &asrt) {
  asrt.GetInnerExpression()->Accept(*this);
  if (*((char*)table_.GetVariable("#tmp")) == 0) {
    throw std::logic_error("Assert statement failed");
  }
}

void Interpreter::Visit(const StatementVariableDeclaration &decl) {
  decl.GetDeclaration()->Accept(*this);
}

void Interpreter::Visit(const StatementNewScope &scope) {
  table_.BeginScope();
  scope.GetStatements()->Accept(*this);
  table_.EndScope();
}

void Interpreter::Visit(const StatementIfReduced &stmt) {
  stmt.GetCondition()->Accept(*this);
  int tmp = *((int*)table_.GetVariable("#tmp"));
  if (tmp) {
    stmt.GetBody()->Accept(*this);
  }
}

void Interpreter::Visit(const StatementIfFull &stmt) {
  stmt.GetCondition()->Accept(*this);
  int tmp = *((int*)table_.GetVariable("#tmp"));
  if (tmp) {
    stmt.GetTrueBody()->Accept(*this);
  } else {
    stmt.GetFalseBody()->Accept(*this);
  }
}

void Interpreter::Visit(const StatementWhile &stmt) {
  while (true) {
    stmt.GetCondition()->Accept(*this);
    int tmp = *((int*)table_.GetVariable("#tmp"));
    if (!tmp) {
      break;
    }
    stmt.GetBody()->Accept(*this);
  }
}

void Interpreter::Visit(const StatementPrint &print) {
  print.GetInnerExpression()->Accept(*this);
  int tmp = *((int*)table_.GetVariable("#tmp"));
  out_ << tmp << '\n';
}

void Interpreter::Visit(const StatementAssignment &stmt) {
  stmt.GetRhs()->Accept(*this);
  stmt.GetLhs()->Accept(*this);
}

void Interpreter::Visit(const StatementReturn &ret) {
  ret.GetInnerExpression()->Accept(*this);
  if (TypeGetter::GetType(*ret.GetInnerExpression(), table_, function_manager_) != waiting_type_.top()) {
    throw std::logic_error("Return value of wrong type");
  }
  returned_ = true;
}

void Interpreter::Visit(const StatementMethodInvocation &invoc) {
  invoc.GetMethod()->Accept(*this);
}

void Interpreter::Visit(const LValueSimple &simple) {
  simple.GetLvalue()->Accept(*this);
};

void Interpreter::Visit(const LValueArrayElement &) {
  throw std::runtime_error("Arrays are not allowed");
}

void Interpreter::Visit(const MethodInvocation &invoc) {
  invoc.GetObject()->Accept(*this);
  invoc.GetArguments()->Accept(*this);
  std::string type_ = TypeGetter::GetType(*invoc.GetObject(), table_, function_manager_);
  auto& func = function_manager_.GetFunction(type_, invoc.GetMethodName());
  waiting_type_.push(func.GetReturningType());
  table_.BeginScope();
  auto& types = func.GetTypes();
  auto& formals = func.GetFormals();
  size_t pos = 0;
  for (size_t i = 0; i < types.size(); ++i) {
    if (types[i] == "int") {
      table_.CreateVariable(formals[i], "int", 4);
      table_.Put(formals[i], (char*)(&function_arguments_[pos]), 4);
      ++pos;
      continue;
    }
    if (types[i] == "boolean") {
      table_.CreateVariable(formals[i], "boolean", 1);
      bool tmp = (function_arguments_[pos] != 0);
      table_.Put(formals[i], (char*)&tmp, 1);
      ++pos;
      continue;
    }
    table_.CreateVariable(formals[i], types[i], 0);
  }
  table_.CreateVariable("this", type_, 0);
  func.GetStatements().Accept(*this);
  if (!returned_ && func.GetReturningType() != "void") {
    throw std::logic_error("Function " + invoc.GetMethodName() + " returned nothing");
  }
  returned_ = false;
  table_.EndScope();
  waiting_type_.pop();
}

void Interpreter::Visit(const StatementList &list) {
  if (list.GetHead() == nullptr || returned_) {
    return;
  }
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void Interpreter::Visit(const ExpressionNumber &num) {
  int tmp = num.GetValue();
  table_.Put("#tmp", (char*)&tmp, 4);
}

void Interpreter::Visit(const ArrayElementLValue &) {
  throw std::runtime_error("No array is allowed");
}

void Interpreter::Visit(const SimpleLValue &lv) {
  std::string type_ = table_.GetType(lv.GetVariableName());
  if (type_ == "int") {
    int tmp = *((int*)table_.GetVariable("#tmp"));
    table_.Put(lv.GetVariableName(), (char*)&tmp, 4);
  }
  if (type_ == "boolean") {
    int tmp = *((int*)table_.GetVariable("#tmp"));
    bool flag = (tmp != 0);
    table_.Put(lv.GetVariableName(), (char*)&flag, 1);
  }
}

void Interpreter::Visit(const Type &) {}

}