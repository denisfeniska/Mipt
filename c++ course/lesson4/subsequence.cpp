#include <iostream>

char FindChar(int k, int len) {
  if (len == 1) {
    return '0';
  }
  int half = len / 2;
  if (k <= half) {
    return FindChar(k, half);
  }
  char prev_char = FindChar(k - half, half);
  if (prev_char == '0') {
    return '1';
  }
  if (prev_char == '1') {
    return '2';
  }
  return '0';
}

int main() {
  int k = 0;
  std::cin >> k;
  int len = 1;
  while (len < k) {
    len *= 2;
  }
  char result = FindChar(k, len);
  std::cout << result << "\n";
  return 0;
}