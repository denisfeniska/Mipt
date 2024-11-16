#include <iostream>

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

bool SameSets() {
  int first_size = 0;
  std::cin >> first_size;
  int* first_arr = new int[first_size];
  for (int i = 0; i < first_size; ++i) {
    int elem = 0;
    std::cin >> elem;
    first_arr[i] = elem;
  }
  int second_size = 0;
  std::cin >> second_size;
  int* second_arr = new int[second_size];
  for (int i = 0; i < second_size; ++i) {
    int elem = 0;
    std::cin >> elem;
    second_arr[i] = elem;
  }
  Sort(first_arr, first_arr + first_size);
  Sort(second_arr, second_arr + second_size);
  int first_count = 0;
  for (int i = 0; i < first_size; ++i) {
    if (i == 0 || first_arr[i] != first_arr[i - 1]) {
      first_arr[first_count] = first_arr[i];
      first_count++;
    }
  }
  int second_count = 0;
  for (int i = 0; i < second_size; ++i) {
    if (i == 0 || second_arr[i] != second_arr[i - 1]) {
      second_arr[second_count] = second_arr[i];
      second_count++;
    }
  }
  bool result = true;
  if (first_count != second_count) {
    result = false;
  } else {
    for (int i = 0; i < first_count; ++i) {
      if (first_arr[i] != second_arr[i]) {
        result = false;
        break;
      }
    }
  }
  delete[] first_arr;
  delete[] second_arr;
  return result;
}

int main() {
  if (SameSets()) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
  return 0;
}