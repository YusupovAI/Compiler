#include "Class.h"
#include "FieldVisitor.h"
#include "SizeManager.h"

void Class::AddField(const std::string & name, const std::string& type_) {
  offsets_[name] = {type_, size_};
  size_ += SizeManager::GetSize(type_);
  auto word_size = SizeManager::GetWordSize();
  if (size_ % word_size != 0) {
    size_ += word_size - size_ % word_size;
  }
}

size_t Class::GetFieldOffset(const std::string &name) const {
  return offsets_.at(name).offset_;
}



Class Class::MakeClass(const AST::DeclarationList* list) {
  Class cl;
  while (list->GetHead() != nullptr) {
    auto *field = FieldVisitor::GetVariable(*list->GetHead().get());
    list = list->GetTail().get();
    if (field == nullptr) {
      continue;
    }
    auto& typ = field->GetVariableType()->GetType();
    cl.AddField(field->GetVariableName(), typ);
  }
  return cl;
}

const std::string &Class::GetFieldType(const std::string &name) const {
  return offsets_.at(name).type_;
}

bool Class::HasField(const std::string &name) const {
  return offsets_.find(name) != offsets_.end();
}

size_t Class::GetSize() const {
  return size_;
}

Class::FieldInfo::FieldInfo(std::string t, size_t o) : type_(std::move(t)), offset_(o) {}
