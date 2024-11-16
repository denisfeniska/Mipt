#ifndef SORT_H
#define SORT_H

template <class T, class U, class R>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, R* out) {
  while (first_begin < first_end && second_begin < second_end) {
    if (*first_begin < *second_begin) {
      *out = *first_begin;
      ++first_begin;
      ++out;
    } else {
      *out = *second_begin;
      ++second_begin;
      ++out;
    }
  }
  while (first_begin < first_end) {
    *out = *first_begin;
    ++first_begin;
    ++out;
  }
  while (second_begin < second_end) {
    *out = *second_begin;
    ++second_begin;
    ++out;
  }
}

template <class T>
void Sort(T* begin, T* end) {
  if (end - begin <= 1) {
    return;
  }
  T* mid = begin + (end - begin) / 2;
  Sort(begin, mid);
  Sort(mid, end);
  T* temp = new T[end - begin];
  Merge(begin, mid, mid, end, temp);
  for (int i = 0; i < end - begin; ++i) {
    begin[i] = temp[i];
  }
  delete[] temp;
}

#endif