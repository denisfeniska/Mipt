#include <iostream>

int main() {
  int count = 0;
  std::cin >> count;
  int* values = new int[count];
  for (int i = 0; i < count; ++i) {
    int value = 0;
    std::cin >> value;
    values[i] = value;
  }
  int dp[1000001];
  for (int i = 0; i < count; ++i) {
    dp[i] = 1;
  }
  int res = 0;
  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < i; ++j) {
      if (values[i] > values[j]) {
        dp[i] = (dp[i] + dp[j]) % 1000000;
      }
    }
    res = (res + dp[i]) % 1000000;
  }
  std::cout << res << "\n";
  delete[] values;
  return 0;
}