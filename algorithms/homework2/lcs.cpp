#include <iostream>
#include <algorithm>

void FillSequence(int* first_sequence, int* second_sequence, int** dp, int first_count, int second_count) {
  for (int i = 1; i < first_count + 1; ++i) {
    for (int j = 1; j < second_count + 1; ++j) {
      if (first_sequence[i - 1] == second_sequence[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
}

void RecoverySequence(int* first_sequence, int* second_sequence, int** dp, int first_count, int second_count) {
  int len = dp[first_count][second_count];
  int* res_arr = new int[len];
  int index = len - 1;
  for (int i = first_count, j = second_count; i > 0 && j > 0;) {
    if (first_sequence[i - 1] == second_sequence[j - 1]) {
      res_arr[index] = first_sequence[i - 1];
      --i;
      --j;
      --index;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }
  for (int i = 0; i < len; ++i) {
    std::cout << res_arr[i] << " ";
  }
  std::cout << "\n";
  delete[] res_arr;
}

int main() {
  int first_count = 0;
  std::cin >> first_count;
  int* first_sequence = new int[first_count];
  for (int i = 0; i < first_count; ++i) {
    int value = 0;
    std::cin >> value;
    first_sequence[i] = value;
  }
  int second_count = 0;
  std::cin >> second_count;
  int* second_sequence = new int[second_count];
  for (int i = 0; i < second_count; ++i) {
    int value = 0;
    std::cin >> value;
    second_sequence[i] = value;
  }
  int** dp = new int*[first_count + 1];
  for (int i = 0; i < first_count + 1; ++i) {
    dp[i] = new int[second_count + 1];
    for (int j = 0; j < second_count + 1; ++j) {
      dp[i][j] = 0;
    }
  }
  FillSequence(first_sequence, second_sequence, dp, first_count, second_count);
  RecoverySequence(first_sequence, second_sequence, dp, first_count, second_count);
  delete[] first_sequence;
  delete[] second_sequence;
  for (int i = 0; i < first_count + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return 0;
}