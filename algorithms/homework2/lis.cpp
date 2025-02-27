#include <iostream>
#include <limits>
#include <algorithm>

void RecoverySequence(int sequence[], int pos[], int prev[], size_t len) {
  int res_arr[1001];
  int index = 0;
  for (int i = pos[len]; i != -1;) {
    res_arr[index] = sequence[i];
    index++;
    i = prev[i];
  }
  for (int i = index - 1; i >= 0; --i) {
    std::cout << res_arr[i] << " ";
  }
  std::cout << "\n";
}

void FillSequence(int sequence[], int count) {
  int d[1001];
  int pos[1001];
  int prev[1001];
  for (int i = 0; i < 1001; ++i) {
    d[i] = std::numeric_limits<int>::max();
    pos[i] = -1;
    prev[i] = -1;
  }
  d[0] = std::numeric_limits<int>::min();
  size_t len = 0;
  for (int i = 0; i < count; ++i) {
    auto j_ptr = std::upper_bound(d, d + count, sequence[i]);
    size_t j = j_ptr - d;
    if (sequence[i] > d[j - 1] && sequence[i] < d[j]) {
      d[j] = sequence[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      if (j > len) {
        len = j;
      }
    }
  }
  RecoverySequence(sequence, pos, prev, len);
}

int main() {
  int count = 0;
  std::cin >> count;
  int sequence[1001];
  for (int i = 0; i < count; ++i) {
    int value = 0;
    std::cin >> value;
    sequence[i] = value;
  }
  FillSequence(sequence, count);
  return 0;
}