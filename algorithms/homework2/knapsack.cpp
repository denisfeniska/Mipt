#include <iostream>

int main() {
  int count = 0;
  int max_weight = 0;
  std::cin >> count >> max_weight;
  int mass[101];
  int cost[101];
  for (int i = 1; i <= count; i++) {
    std::cin >> mass[i];
  }
  for (int i = 1; i <= count; i++) {
    std::cin >> cost[i];
  }
  int dp[101][10001] = {};
  int check[101][10001] = {};
  for (int i = 1; i <= count; i++) {
    for (int j = 0; j <= max_weight; j++) {
      if (mass[i] <= j && dp[i - 1][j - mass[i]] + cost[i] > dp[i - 1][j]) {
        dp[i][j] = dp[i - 1][j - mass[i]] + cost[i];
        check[i][j] = 1;
      } else {
        dp[i][j] = dp[i - 1][j];
        check[i][j] = 0;
      }
    }
  }
  int index = max_weight;
  int res[101];
  int res_size = 0;
  for (int i = count; i > 0; i--) {
    if (check[i][index] == 1) {
      res[res_size++] = i;
      index -= mass[i];
    }
  }
  for (int i = res_size - 1; i >= 0; i--) {
    std::cout << res[i] << "\n";
  }
  return 0;
}