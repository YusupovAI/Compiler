#include "Class.h"
#include "FieldVisitor.h"

void Class::AddField(const std::string & name, size_t len) {
  offsets_[name] = size_;
  size_ += len;
}

size_t Class::GetFieldOffset(const std::string &name) const {
  return offsets_.at(name);
}



Class Class::MakeClass(const AST::DeclarationList* list) {
  Class cl;
  while (list->GetHead() != nullptr) {
    auto *field = FieldVisitor::GetVariable(*list->GetHead().get());
    auto typ = field->GetVariableType()->GetType();
    size_t len = 8;
    if (typ == "int") {
      len = 4;
    }
    if (typ == "boolean") {
      len = 1;
    }
    cl.AddField(field->GetVariableName(), len);
    list = list->GetTail().get();
  }
  return cl;
}
