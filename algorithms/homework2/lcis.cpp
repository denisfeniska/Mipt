#include <iostream>
#include <algorithm>

void FillLcis(int seq1[], int count1, int seq2[], int count2) {
  int dp[501] = {};
  int prev[501] = {};
  int max_len = 0;
  int max_index = -1;
  for (int i = 0; i < count1; ++i) {
    int best = 0;
    int best_index = -1;
    for (int j = 0; j < count2; ++j) {
      if (seq1[i] == seq2[j]) {
        dp[j] = std::max(dp[j], best + 1);
        prev[j] = best_index;
      }
      if (seq1[i] > seq2[j]) {
        if (dp[j] > best) {
          best = dp[j];
          best_index = j;
        }
      }
    }
  }
  for (int j = 0; j < count2; ++j) {
    if (dp[j] > max_len) {
      max_len = dp[j];
      max_index = j;
    }
  }


  int sequence[501];
  int len = 0;
  while (max_index != -1) {
    sequence[len++] = seq2[max_index];
    max_index = prev[max_index];
  }


  
  std::cout << max_len << "\n";
  for (int i = len - 1; i >= 0; --i) {
    std::cout << sequence[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  int count1 = 0;
  int count2 = 0;
  int seq1[501];
  int seq2[501];
  std::cin >> count1;
  for (int i = 0; i < count1; ++i) {
    std::cin >> seq1[i];
  }
  std::cin >> count2;
  for (int i = 0; i < count2; ++i) {
    std::cin >> seq2[i];
  }
  FillLcis(seq1, count1, seq2, count2);
  return 0;
}