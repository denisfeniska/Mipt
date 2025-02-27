#ifndef ARRAY_H
#define ARRAY_H
#define ARRAY_TRAITS_IMPLEMENTED

#include <cstdint>
#include <algorithm>

template <class T, size_t N>
class Array {
 public:
  T values[N];

  const T& operator[](size_t index) const {
    return values[index];
  }

  T& operator[](size_t index) {
    return values[index];
  }

  T& Front() {
    return values[0];
  }

  const T& Front() const {
    return values[0];
  }

  T& Back() {
    return values[N - 1];
  }

  const T& Back() const {
    return values[N - 1];
  }

  T* Data() {
    return values;
  }

  const T* Data() const {
    return values;
  }

  size_t Size() const {
    return N;
  }
  
  bool Empty() const {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      values[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(values[i], other[i]);
    }
  }
};

template <class T, size_t N>
size_t GetSize(const T (&)[N]) {
  return N;
}

template <class T>
size_t GetSize(const T&) {
  return 0;
}

template <class T>
size_t GetRank(const T&) {
  return 0;
}

template <class T, size_t N>
size_t GetRank(const T (&a)[N]) {
  return 1 + GetRank(a[0]);
}

template <class T>
size_t GetNumElements(const T&) {
  return 1;
}

template <class T, size_t N>
size_t GetNumElements(const T (&a)[N]) {
  return N * GetNumElements(a[0]);
}

#endif