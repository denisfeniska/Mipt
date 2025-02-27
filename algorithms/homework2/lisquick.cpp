#include <iostream>
#include <algorithm>
#include <limits>

int LisLength(int sequence[], int count) {
  int table[1001][1001];
  int row_lengths[1001] = {0};
  int rows_count = 0;
  for (int i = 0; i < count; ++i) {
    int row = -1;
    for (int j = 0; j < rows_count; ++j) {
      if (table[j][row_lengths[j] - 1] >= sequence[i]) {
        row = j;
        break;
      }
    }
    if (row == -1) {
      table[rows_count][0] = sequence[i];
      row_lengths[rows_count] = 1;
      rows_count++;
    } else {
      auto pos = std::upper_bound(table[row], table[row] + row_lengths[row], sequence[i]);
      if (pos != table[row] + row_lengths[row]) {
        *pos = sequence[i];
      }
    }
  }
  return rows_count;
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
  std::cout << LisLength(sequence, count) << "\n";
  return 0;
}
