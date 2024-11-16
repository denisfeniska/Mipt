#ifndef HEAPSORT_H
#define HEAPSORT_H

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
void SiftDown(T begin, __SIZE_TYPE__ index, __SIZE_TYPE__ size) {
  while (true) {
    __SIZE_TYPE__ left_index = 2 * index + 1;
    __SIZE_TYPE__ right_index = 2 * index + 2;
    __SIZE_TYPE__ max_value_index = index;
    if (left_index < size && *(begin + max_value_index) < *(begin + left_index)) {
      max_value_index = left_index;
    }
    if (right_index < size && *(begin + max_value_index) < *(begin + right_index)) {
      max_value_index = right_index;
    }
    if (max_value_index == index) {
      break;
    }
    Swap(*(begin + index), *(begin + max_value_index));
    index = max_value_index;
  }
}

template <class T>
void MakeHeap(T begin, T end) {
  __SIZE_TYPE__ size = end - begin;
  if (size <= 1) {
    return;
  }
  for (__SIZE_TYPE__ i = size; i > 0; --i) {
    SiftDown(begin, i - 1, size);
  }
}

template <class T>
void SortHeap(T begin, T end) {
  MakeHeap(begin, end);
  __SIZE_TYPE__ size = end - begin;
  for (__SIZE_TYPE__ i = size - 1; i > 0; --i) {
    Swap(*begin, *(begin + i));
    SiftDown(begin, 0, i);
  }
}

#endif