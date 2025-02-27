#include <iostream>

int main() {
  int count = 0;
  std::cin >> count;
  if (count == 1) {
    std::cout << 2 << "\n";
    return 0;
  }
  if (count == 2) {
    std::cout << 3 << "\n";
    return 0;
  }
  auto dp = new __INT64_TYPE__[count + 1];
  dp[1] = 2;
  dp[2] = 3;
  for (int i = 3; i < count + 1; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  std::cout << dp[count] << "\n";
  delete[] dp;
  return 0;
}