#ifndef TEMPLATE_H
#define TEMPLATE_H

template <class T, class U>
bool BinarySearch(T* begin, T* end, const U& value) {
  while (begin < end) {
    T* middle = begin + (end - begin) / 2;
    if (*middle < value) {
      begin = middle + 1;
    } else if (value < *middle) {
      end = middle;
    } else {
      return true;
    }
  }
  return false;
}

template <class T, class U>
T* LowerBound(T* begin, T* end, const U& value) {
  while (begin < end) {
    T* middle = begin + (end - begin) / 2;
    if (*middle < value) {
      begin = middle + 1;
    } else {
      end = middle;
    }
  }
  return begin;
}

template <class T, class U>
T* UpperBound(T* begin, T* end, const U& value) {
  while (begin < end) {
    T* middle = begin + (end - begin) / 2;
    if (value < *middle) {
      end = middle;
    } else {
      begin = middle + 1;
    }
  }
  return begin;
}

#endif