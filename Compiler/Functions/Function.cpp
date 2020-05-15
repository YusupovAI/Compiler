#include "FunctionSignature.h"
#include "TypeGetter.h"

FunctionSignature::FunctionSignature(std::vector<Type> types, std::vector<std::string> formals)
: types_(std::move(types)),
formals_(std::move(formals)){}

const std::vector<typename FunctionSignature::Type> &FunctionSignature::GetTypes() const {
  return types_;
}

const std::vector<std::string>& FunctionSignature::Formals() const {
  return formals_;
}

FunctionSignature FunctionSignature::MakeFunction(AST::MethodDeclaration &decl) {
  auto head = decl.GetFormals().get();
  std::vector<typename FunctionSignature::Type> types;
  std::vector<std::string> formals;
  AST::TypeGetter resolver;
  while (head->GetHeadType() != nullptr) {
    head->GetHeadType()->Accept(resolver);
    types.push_back(resolver.GetType());
    formals.push_back(head->GetHeadName());
    head = head->GetTail().get();
  }
  return {std::move(types), std::move(formals)};
}
