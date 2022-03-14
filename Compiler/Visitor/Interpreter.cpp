#include "Interpreter.h"
#include "FunctionManagerCreator.h"
#include "ClassManagerCreator.h"
#include "TypeGetter.h"
#include "SizeManager.h"

#include <cstdlib>

namespace AST {

Interpreter::Interpreter(std::ostream &out,
                         const FunctionManager &function_manager,
                         const ClassManager &class_manager)
    : out_(out),
      function_manager_(function_manager),
      class_manager_(class_manager) {}

void Interpreter::Visit(const ExpressionAdd &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = left + right;
}

void Interpreter::Visit(const ExpressionSub &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = left - right;
}

void Interpreter::Visit(const ExpressionMul &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = left * right;
}

void Interpreter::Visit(const ExpressionDiv &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = left / right;
}

void Interpreter::Visit(const ExpressionAnd &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = left && right;
}

void Interpreter::Visit(const ExpressionOr &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = left || right;
}

void Interpreter::Visit(const ExpressionEqual &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = (left == right);
}

void Interpreter::Visit(const ExpressionMod &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = left % right;
}

void Interpreter::Visit(const ExpressionLess &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = (left < right);
}

void Interpreter::Visit(const ExpressionGreater &exp) {
  exp.GetLeft()->Accept(*this);
  int left = tos_value_;
  exp.GetRight()->Accept(*this);
  int right = tos_value_;
  tos_value_ = (left > right);
}

void Interpreter::Visit(const ExpressionFalse &exp) {
  tos_value_ = 0;
}

void Interpreter::Visit(const ExpressionTrue &exp) {
  tos_value_ = 1;
}

void Interpreter::Visit(const ExpressionArrayElement &exp) {
  exp.GetArray()->Accept(*this);
  char *ptr = (char *) tos_value_;
  exp.GetIndex()->Accept(*this);
  int idx = tos_value_;
  if (ptr == nullptr) {
    throw std::logic_error("Usage of uninitialized array");
  }
  if (*(uint64_t *) ptr <= idx) {
    throw std::logic_error("Trying to use index out of bound");
  }
  std::string type_ = TypeGetter::GetType(exp, table_, function_manager_, class_manager_);
  if (type_ == "int") {
    tos_value_ = *(int *) (ptr + 8 + idx * 4);
  } else {
    if (type_ == "boolean") {
      tos_value_ = *(bool *) (ptr + 8 + idx);
    } else {
      tos_value_ = *(int64_t *) (ptr + 8 + idx * 8);
    }
  }
}

void Interpreter::Visit(const ExpressionLength &exp) {
  exp.GetLhs()->Accept(*this);
  char* ptr = (char*)tos_value_;
  if (ptr == nullptr) {
    throw std::logic_error("Usage of uninitialized array");
  }
  tos_value_ = *(int64_t*)ptr;
}

void Interpreter::Visit(const ExpressionNewVariable &exp) {
  tos_value_ = (int64_t) calloc(1, class_manager_.GetClass(exp.GetTypeName()).GetSize());
}

void Interpreter::Visit(const ExpressionNewArray &exp) {
  std::string type_ = exp.GetArrayType()->GetType();
  exp.GetArraySize()->Accept(*this);
  if (tos_value_ < 0) {
    throw std::logic_error("Trying to allocate array of negative size");
  }
  char* ptr = (char*)calloc(8 + SizeManager::GetSize(type_) * tos_value_, 1);
  *(int64_t*)ptr = tos_value_;
  tos_value_ = (int64_t)ptr;
}

void Interpreter::Visit(const ExpressionNot &exp) {
  tos_value_ = !tos_value_;
}

void Interpreter::Visit(const ExpressionBraces &exp) {
  exp.GetInnerExpression()->Accept(*this);
}

void Interpreter::Visit(const ExpressionVariable &exp) {
  std::string class_name;
  if (!table_.HasVariable(exp.GetVariableName())) {
    class_name = table_.GetVariableType("this");
    tos_value_ = (int64_t) (*(char **) table_.GetVariable("this")
        + class_manager_.GetClass(class_name).GetFieldOffset(exp.GetVariableName()));
  } else {
    class_name = table_.GetVariableType(exp.GetVariableName());
    tos_value_ = (int64_t) table_.GetVariable(exp.GetVariableName());
  }
  if (class_name == "boolean") {
    tos_value_ = *((bool *) tos_value_);
  } else {
    if (class_name == "int") {
      tos_value_ = *((int *) tos_value_);
    } else {
      tos_value_ = *((int64_t *) tos_value_);
    }
  }
}

void Interpreter::Visit(const ExpressionThis &exp) {
  tos_value_ = *((int64_t *) table_.GetVariable("this"));
}

void Interpreter::Visit(const ExpressionMethodInvocation &exp) {
  exp.GetMethod()->Accept(*this);
}

void Interpreter::Visit(const FunctionArguments &args) {
  const FunctionArguments *cur = &args;
  std::vector<int64_t> exprs;
  while (cur->GetHead() != nullptr) {
    std::string type_ = TypeGetter::GetType(*cur->GetHead().get(), table_, function_manager_, class_manager_);
    cur->GetHead()->Accept(*this);
    exprs.push_back(tos_value_);
    cur = cur->GetTail().get();
  }
  function_arguments_ = std::move(exprs);
}

void Interpreter::Visit(const Program &program) {
  table_.BeginScope();
  program.GetMainClass()->Accept(*this);
  table_.EndScope();
}

void Interpreter::Visit(const ClassDeclarationList &) {}

void Interpreter::Visit(const ClassDeclarationSimple &) {}

void Interpreter::Visit(const ClassDeclarationInheritted &) {}

void Interpreter::Visit(const DeclarationList &) {}

void Interpreter::Visit(const DeclarationVariable &decl) {
  decl.GetDeclaration()->Accept(*this);
}

void Interpreter::Visit(const DeclarationMethod &decl) {}

void Interpreter::Visit(const VariableDeclaration &decl) {
  auto &type_ = decl.GetVariableType()->GetType();
  table_.CreateVariable(decl.GetVariableName(), decl.GetVariableType()->GetType(), false);
}

void Interpreter::Visit(const MethodDeclaration &decl) {}

void Interpreter::Visit(const Formals &) {}

void Interpreter::Visit(const MainClass &cls) {
  cls.GetStatements()->Accept(*this);
}

void Interpreter::Visit(const StatementAssert &asrt) {
  asrt.GetInnerExpression()->Accept(*this);
  if (!tos_value_) {
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
  if (tos_value_) {
    stmt.GetBody()->Accept(*this);
  }
}

void Interpreter::Visit(const StatementIfFull &stmt) {
  stmt.GetCondition()->Accept(*this);
  if (tos_value_) {
    stmt.GetTrueBody()->Accept(*this);
  } else {
    stmt.GetFalseBody()->Accept(*this);
  }
}

void Interpreter::Visit(const StatementWhile &stmt) {
  while (true) {
    stmt.GetCondition()->Accept(*this);
    if (!tos_value_) {
      break;
    }
    stmt.GetBody()->Accept(*this);
  }
}

void Interpreter::Visit(const StatementPrint &print) {
  print.GetInnerExpression()->Accept(*this);
  out_ << tos_value_ << '\n';
}

void Interpreter::Visit(const StatementAssignment &stmt) {
  stmt.GetRhs()->Accept(*this);
  stmt.GetLhs()->Accept(*this);
}

void Interpreter::Visit(const StatementReturn &ret) {
  ret.GetInnerExpression()->Accept(*this);
  if (TypeGetter::GetType(*ret.GetInnerExpression(), table_, function_manager_, class_manager_)
      != waiting_type_.top()) {
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

void Interpreter::Visit(const LValueArrayElement &elem) {
  elem.GetLvalue()->Accept(*this);
}

void Interpreter::Visit(const MethodInvocation &invoc) {
  invoc.GetObject()->Accept(*this);
  int64_t ptr = tos_value_;
  if (ptr == 0) {
    throw std::logic_error("Trying to call method from non-initialized object");
  }
  std::string type_ = TypeGetter::GetType(*invoc.GetObject(), table_, function_manager_, class_manager_);
  invoc.GetArguments()->Accept(*this);
  auto &func = function_manager_.GetFunction(type_, invoc.GetMethodName());
  waiting_type_.push(func.GetReturningType());
  auto last_table = std::move(table_);
  table_ = SymbolTable();
  auto &types = func.GetTypes();
  auto &formals = func.GetFormals();
  size_t pos = 0;
  table_.BeginScope();
  for (size_t i = 0; i < types.size(); ++i) {
    table_.CreateVariable(formals[i], types[i], false);
    table_.Put(formals[i], (char *) (&function_arguments_[i]));
  }
  table_.CreateVariable("this", type_, false);
  table_.Put("this", (char *) &ptr);
  func.GetStatements().Accept(*this);
  if (!returned_ && func.GetReturningType() != "void") {
    throw std::logic_error("Function " + invoc.GetMethodName() + " returned nothing");
  }
  returned_ = false;
  table_.EndScope();
  table_ = std::move(last_table);
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
  tos_value_ = num.GetValue();
}

void Interpreter::Visit(const ArrayElementLValue &elem) {
  int tmp = tos_value_;
  elem.GetArray()->Accept(*this);
  char* ptr = (char*)tos_value_;
  if (ptr == nullptr) {
    throw std::logic_error("Usage of uninitialized array");
  }
  elem.GetIndex()->Accept(*this);
  if (*(int64_t*)ptr <= tos_value_) {
    throw std::logic_error("Array index is out of bound");
  }
  std::string type_ = TypeGetter::GetType(*elem.GetArray(), table_, function_manager_, class_manager_);
//  delete []
  type_.pop_back();
  type_.pop_back();
  int idx = tos_value_;
  if (type_ == "boolean") {
    *(bool*)(ptr + 8 + idx) = (tmp != 0);
  } else {
    if (type_ == "int") {
      *(int*)(ptr + 8 + idx * 4) = tmp;
    } else {
      *(int64_t*)(ptr + 8 * (idx + 1)) = tmp;
    }
  }
}

void Interpreter::Visit(const SimpleLValue &lv) {
  std::string class_name;
  int64_t tmp = tos_value_;
  if (!table_.HasVariable(lv.GetVariableName())) {
    class_name = table_.GetVariableType("this");
    tos_value_ = (int64_t) (*(char **) table_.GetVariable("this")
        + class_manager_.GetClass(class_name).GetFieldOffset(lv.GetVariableName()));
  } else {
    class_name = table_.GetVariableType(lv.GetVariableName());
    tos_value_ = (int64_t) table_.GetVariable(lv.GetVariableName());
  }
  if (class_name == "boolean") {
    *(bool *) tos_value_ = tmp;
  } else {
    if (class_name == "int") {
      *(int *) tos_value_ = tmp;
    } else {
      *(int64_t *) tos_value_ = tmp;
    }
  }
}

void Interpreter::Visit(const Type &) {}

}