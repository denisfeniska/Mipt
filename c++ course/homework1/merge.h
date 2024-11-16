#ifndef MERGE_H
#define MERGE_H

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

#endif