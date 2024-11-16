#ifndef PRIORITYTQUEUE_H
#define PRIORITYTQUEUE_H

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
void PushHeap(T* begin, T* end) {
  if (begin == end) {
    return;
  }
  int last_index = end - begin - 1;
  int parent_index = 0;
  while (last_index > 0) {
    parent_index = (last_index - 1) / 2;
    if (begin[parent_index] < begin[last_index]) {
      Swap(begin[parent_index], begin[last_index]);
      last_index = parent_index;
    } else {
      break;
    }
  }
}

template <class T>
void PopHeap(T* begin, T* end) {
  if (end - begin < 2) {
    return;
  }
  Swap(*begin, *(end - 1));
  int size = end - begin - 1;
  int index = 0;
  while (true) {
    int left_index = index * 2 + 1;
    int right_index = index * 2 + 2;
    int max_value_index = index;
    if (left_index < size && begin[max_value_index] < begin[left_index]) {
      max_value_index = left_index;
    }
    if (right_index < size && begin[max_value_index] < begin[right_index]) {
      max_value_index = right_index;
    }
    if (max_value_index == index) {
      break;
    }
    Swap(begin[index], begin[max_value_index]);
    index = max_value_index;
  }
}

#endif