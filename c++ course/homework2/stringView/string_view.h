#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <cstdint>

class StringView {
 private:
  const char* values_;
  std::size_t size_;

 public:
  StringView() : values_(nullptr), size_(0) {}

  StringView(const char* string); // NOLINT

  StringView(const char* string, std::size_t length) : values_(string), size_(string ? length : 0) {};

  char operator[](std::size_t index) const;

  char Front() const;

  char Back() const;

  std::size_t Size() const;

  std::size_t Length() const;

  bool Empty() const;

  const char* Data() const;

  void Swap(StringView& second_string);

  void RemovePrefix(std::size_t prefix_size);

  void RemoveSuffix(std::size_t suffix_size);

  StringView Substr(std::size_t pos, std::size_t count = -1);
};

#endif