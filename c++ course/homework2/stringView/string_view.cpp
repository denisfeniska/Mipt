#include "string_view.h"
#include <algorithm>
#include <cstdint>

StringView::StringView(const char* string) : values_(string), size_(0) {
  if (string) {
    while (string[size_] != '\0') {
      ++size_;
    }
  }
}

char StringView::operator[](size_t index) const {
  return values_[index];
}

char StringView::Front() const {
  return values_[0];
}

char StringView::Back() const {
  return values_[size_ - 1];
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return size_ == 0;
}

const char* StringView::Data() const {
  return values_;
}

void StringView::Swap(StringView& second_string) {
  std::swap(values_, second_string.values_);
  std::swap(size_, second_string.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  values_ = values_ + prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  size_t new_size = 0;
  if (count < size_ - pos) {
    new_size = count;
  } else {
    new_size = size_ - pos;
  }
  return {values_ + pos, new_size};;
}