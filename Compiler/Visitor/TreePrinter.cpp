#include "TreePrinter.h"

namespace AST {

class SpaceWrapper {
 public:
  SpaceWrapper(std::ostream& out, size_t& space_count) : out_(out), space_count_(space_count) {
    for (size_t i = 0; i < space_count_; ++i) {
      out << ' ';
    }
    ++space_count_;
  }

  ~SpaceWrapper() {
    --space_count_;
  }

 private:
  std::ostream& out_;
  size_t& space_count_;
};

TreePrinter::TreePrinter(std::ostream& out) : out_(out), space_count_(0) {}

void TreePrinter::Visit(const ExpressionAdd& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp + Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionSub& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp - Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionMul& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp * Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionDiv& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp / Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionAnd& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp && Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}
  
void TreePrinter::Visit(const ExpressionOr& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp || Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionEqual& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp == Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionMod& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp % Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionLess& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp < Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);  
}

void TreePrinter::Visit(const ExpressionGreater& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp > Exp\n";
  exp.GetLeft()->Accept(*this);
  exp.GetRight()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionFalse& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> False\n";
}

void TreePrinter::Visit(const ExpressionTrue& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> True\n";
}

void TreePrinter::Visit(const ExpressionArrayElement& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp [ Exp ]\n";
  exp.GetArray()->Accept(*this);
  exp.GetIndex()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionLength& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> Exp . length\n";
  exp.GetLhs()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionNewVariable& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> new Type()\n";
  {
    SpaceWrapper wrap(out_, space_count_);
    out_ << "Type ==> ";
    out_ << exp.GetTypeName() << '\n';
  }
}

void TreePrinter::Visit(const ExpressionNewArray& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> new Type[ Exp ]";
  exp.GetArrayType()->Accept(*this);
  exp.GetArraySize()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionNot& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> !Exp\n";
  exp.GetBoolExpression()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionBraces& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> ( Exp )\n";
  exp.GetInnerExpression()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionVariable& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> ";
  out_ << exp.GetVariableName() << '\n';
}

void TreePrinter::Visit(const ExpressionThis& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> this\n";
}

void TreePrinter::Visit(const ExpressionMethodInvocation& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Exp ==> MethodInvocation\n";
  exp.GetMethod()->Accept(*this);
}

void TreePrinter::Visit(const FunctionArguments& exp) {
  SpaceWrapper wrap(out_, space_count_);
  if (exp.GetHead() == nullptr) {
    out_ << "FunctionArguments ==> \n";
    return;
  }
  out_ << "FunctionArguments ==> Exp, FunctionArguments\n";
  exp.GetHead()->Accept(*this);
  exp.GetTail()->Accept(*this);
}

void TreePrinter::Visit(const Program& program) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Program ==> MainClass ClassDeclarationList\n";
  program.GetMainClass()->Accept(*this);
  program.GetClassesDeclaration()->Accept(*this);
}

void TreePrinter::Visit(const ClassDeclarationList& list) {
  SpaceWrapper wrap(out_, space_count_);
  if (list.GetHead() == nullptr) {
    out_ << "ClassDeclarationList ==> \n";
    return;
  }
  out_ << "ClassDeclarationList ==> ClassDeclaration ClassDeclarationList\n";
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void TreePrinter::Visit(const ClassDeclarationSimple& decl) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "ClassDeclaration ==> " << decl.GetClassName() << " { DeclarationList }\n";
  decl.GetDeclarations()->Accept(*this);
}

void TreePrinter::Visit(const ClassDeclarationInheritted& decl) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "ClassDeclaration ==> " << decl.GetClassName() << " : " << decl.GetParentName() << " { DeclarationList }\n";
  decl.GetDeclarations()->Accept(*this);
}

void TreePrinter::Visit(const DeclarationList& list) {
  SpaceWrapper wrap(out_, space_count_);
  if (list.GetHead() == nullptr) {
    out_ << "DeclarationList ==> \n";
    return;
  }
  out_ << "DeclarationList ==> Declaration DeclarationList\n";
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void TreePrinter::Visit(const DeclarationVariable& decl) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Declaration ==> VariableDeclaration\n";
  decl.GetDeclaration()->Accept(*this);
}


void TreePrinter::Visit(const DeclarationMethod& decl) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Declaration ==> MethodDeclaration\n";
  decl.GetDeclaration()->Accept(*this);
}


void TreePrinter::Visit(const VariableDeclaration& decl) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "VariableDeclaration ==> Type " << decl.GetVariableName() << '\n';
  decl.GetVariableType()->Accept(*this);
}

void TreePrinter::Visit(const MethodDeclaration& decl) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "MethodDeclaration ==> Type " << decl.GetMethodName() << "(Formals) {StatementList}\n";
  decl.GetReturnType()->Accept(*this);
  decl.GetFormals()->Accept(*this);
  decl.GetStatements()->Accept(*this);
}

void TreePrinter::Visit(const TypeSimple& simple) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Type ==> SimpleType\n";
  simple.GetType()->Accept(*this);
}

void TreePrinter::Visit(const TypeArray& array) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Type ==> ArrayType\n";
  array.GetType()->Accept(*this);
}

void TreePrinter::Visit(const ArrayType& array) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "ArrayType ==> Type []\n";
  array.GetType()->Accept(*this);
}

void TreePrinter::Visit(const Formals& formals) {
  SpaceWrapper wrap(out_, space_count_);
  if (formals.GetHeadName().empty()) {
    out_ << "FormalList ==> \n";
    return;
  }
  out_ << "Type " << formals.GetHeadName() << ", FormalList\n";
  formals.GetHeadType()->Accept(*this);
  formals.GetTail()->Accept(*this);
}

void TreePrinter::Visit(const MainClass& main_class) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "MainClass ==> public static void main() { StatementList }\n";
  main_class.GetStatements()->Accept(*this);
}

void TreePrinter::Visit(const StatementAssert& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> assert ( Exp )\n";
  st.GetInnerExpression()->Accept(*this);
}

void TreePrinter::Visit(const StatementVariableDeclaration& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> VariableDeclaration\n";
  st.GetDeclaration()->Accept(*this);
}

void TreePrinter::Visit(const StatementNewScope& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> { StatementList }\n";
  st.GetStatements()->Accept(*this);
}

void TreePrinter::Visit(const StatementIfReduced& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> if ( Exp ) Statement\n";
  st.GetCondition()->Accept(*this);
  st.GetBody()->Accept(*this);
}

void TreePrinter::Visit(const StatementIfFull& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> if ( Exp ) Statement else Statement\n";
  st.GetCondition()->Accept(*this);
  st.GetTrueBody()->Accept(*this);
  st.GetFlaseBody()->Accept(*this);
}

void TreePrinter::Visit(const StatementWhile& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> whie ( Exp ) Statement\n";
  st.GetCondition()->Accept(*this);
  st.GetBody()->Accept(*this);
}

void TreePrinter::Visit(const StatementPrint& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> System.out.println( Exp )\n";
  st.GetInnerExpression()->Accept(*this);
}

void TreePrinter::Visit(const StatementAssignment& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> LValue = Exp\n";
  st.GetLhs()->Accept(*this);
  st.GetRhs()->Accept(*this);
}

void TreePrinter::Visit(const StatementReturn& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> return Exp\n";
  st.GetInnerExpression()->Accept(*this);
}

void TreePrinter::Visit(const StatementMethodInvocation& st) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Statement ==> MethodInvocation\n";
  st.GetMethod()->Accept(*this);
}

void TreePrinter::Visit(const LValueSimple& lv) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "LValueSimple ==> SimpleLValue\n";
  lv.GetLvalue()->Accept(*this);
}

void TreePrinter::Visit(const LValueArrayElement& lv) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "LValueArrayElement ==> ArrayElementLValue\n";
  lv.GetLvalue()->Accept(*this);
}

void TreePrinter::Visit(const MethodInvocation& method) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "MethodInvocation ==> Expression . " << method.GetMethodName() << "(ArgumentList)\n";
  method.GetObject()->Accept(*this);
  method.GetArguments()->Accept(*this);
}

void TreePrinter::Visit(const StatementList& list) {
  SpaceWrapper wrap(out_, space_count_);
  if (list.GetHead() == nullptr) {
    out_ << "StatementList ==> \n";
    return;
  }
  out_ << "Statement StatementList\n";
  list.GetHead()->Accept(*this);
  list.GetTail()->Accept(*this);
}

void TreePrinter::Visit(const ExpressionNumber& exp) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "Expression ==> " << exp.GetValue() << '\n';
}

void TreePrinter::Visit(const SimpleType& simple) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "SimpleType ==> ";
  auto result = simple.GetType();
  try {
    SimpleType::Primitive primitive = std::get<SimpleType::Primitive>(result);
    if (primitive == SimpleType::Primitive::Boolean) {
      out_ << "Boolean";
    }
    if (primitive == SimpleType::Primitive::Int) {
      out_ << "Int";
    }
    if (primitive == SimpleType::Primitive::Void) {
      out_ << "Void";
    }
    out_ << '\n';
  } catch(...) {
    auto type_name = std::get<std::string>(result);
    out_ << type_name << '\n';
  }
}

void TreePrinter::Visit(const ArrayElementLValue& lv) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "ArrayElementLValue ==> Exp [ Exp ]\n";
  lv.GetArray()->Accept(*this);
  lv.GetIndex()->Accept(*this);
}

void TreePrinter::Visit(const SimpleLValue& lv) {
  SpaceWrapper wrap(out_, space_count_);
  out_ << "SimpleLValue ==> " << lv.GetVariableName() << '\n';
}

} // namespace AST