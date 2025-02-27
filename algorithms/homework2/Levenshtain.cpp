#include <iostream>

int main() {
  char str1[5001];
  char str2[5001];
  std::cin >> str1 >> str2;
  int size1 = 0;
  int size2 = 0;
  while (str1[size1] != '\0') {
    ++size1;
  }
  while (str2[size2] != '\0') {
    ++size2;
  }
  int dp[5001][5001];
  for (int i = 0; i < size1 + 1; ++i) {
    dp[i][0] = i;
  }
  for (int i = 0; i < size2 + 1; ++i) {
    dp[0][i] = i;
  }
  for (int i = 1; i < size1 + 1; ++i) {
    for (int j = 1; j < size2 + 1; ++j) {
      if (str1[i - 1] == str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        int deletion = dp[i - 1][j] + 1;
        int insertion = dp[i][j - 1] + 1;
        int substitution = dp[i - 1][j - 1] + 1;
        dp[i][j] = deletion;
        if (insertion < dp[i][j]) {
          dp[i][j] = insertion;
        }
        if (substitution < dp[i][j]) {
          dp[i][j] = substitution;
        }
      }
    }
  }
  std::cout << dp[size1][size2] << "\n";
  return 0;
}