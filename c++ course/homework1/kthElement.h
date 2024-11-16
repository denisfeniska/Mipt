#ifndef KTHELEMENT_H
#define KTHELEMENT_H

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
T Partition(T begin, T end) {
  auto pivot = *begin;
  T left = begin + 1;
  T right = end - 1;
  while (true) {
    while (!(right < left)) {
      if (*left < pivot) {
        ++left;
      } else {
        break;
      }
    }
    while (!(right < left)) {
      if (!(*right < pivot)) {
        --right;
      } else {
        break;
      }
    }
    if (left < right) {
      Swap(*left, *right);
    } else {
      break;
    }
  }
  Swap(*begin, *right);
  return right;
}

template <class T>
void KthElement(T begin, T k, T end) {
  while (begin < end) {
    T pivot = Partition(begin, end);
    if (pivot == k) {
      return;
    }
    if (pivot < k) {
      begin = pivot + 1;
    } else {
      end = pivot;
    }
  }
}

#endif