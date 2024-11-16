#include <iostream>

void Subsequence(int n, int* result, int& index) {
  if (n <= 1) {
    result[index++] = 1;
    return;
  }
  if (n == 2) {
    std::cout << 1 << " " << 2 << " ";
    return;
  }
  for (int i = 2; i <= (n - 1) * 2; i++) {
    if (i % 2 == 0) {
      result[index++] = i / 2 + 1;
    } else {
      result[index++] = -1 * (i - 1) / 2;
    }
  }
  if (n - 2 > 1) {
    Subsequence(n - 2, result, index);
  } else if (n - 2 == 1) {
    result[index++] = 1;
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  int result[10000] = {0};
  int index = 0;
  Subsequence(n, result, index);
  for (int i = 0; i < index; i++) {
      std::cout << result[i] << " ";
  }
  return 0;
}
