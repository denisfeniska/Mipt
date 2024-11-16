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

bool Check(int n, int m, int k, int scope, int* votes) {
  int count_groups = 0;
  for (int i = 0; i + k <= n;) {
    int min_vote = votes[i];
    int max_vote = votes[i + k - 1];
    if (max_vote - min_vote <= scope) {
      count_groups++;
      i += k;
    } else {
      ++i;
    }
  }
  return count_groups >= m;
}

int main() {
  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m >> k;
  int* votes = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> votes[i];
  }
  Sort(votes, votes + n);
  int min_scope = 0;
  int max_scope = votes[n - 1] - votes[0];
  while (min_scope < max_scope) {
    int scope = min_scope + (max_scope - min_scope) / 2;
    if (Check(n, m, k, scope, votes)) {
      max_scope = scope;
    } else {
      min_scope = scope + 1;
    }
  }
  std::cout << min_scope << "\n";
  delete[] votes;
  return 0;
}