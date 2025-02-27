#include <iostream>

void LCIS(int seq1[], int seq1_count, int seq2[], int seq2_count) {
  int dp[501][501] = {};
  int len = 0;
  int sequence[501];
  for (int i = 0; i < seq1_count; i++) {
    for (int j = 0; j < seq2_count; j++) {
      if (seq1[i] == seq2[j]) {
        dp[i][j] = 1;
        for (int k = 0; k < i; k++) {
          if (dp[k][j] + 1 > dp[i][j] && seq1[k] < seq1[i]) {
            dp[i][j] = dp[k][j] + 1;
          }
        }
      } else if (j > 0) {
        dp[i][j] = dp[i][j - 1];
      }
    }
  }
  int max_index = -1;
  for (int row = 0; row < seq1_count; ++row) {
    int value = dp[row][seq2_count - 1];
    if (value > len) {
      len = value;
      max_index = row;
    }
  }
  if (len == 0) {
    std::cout << '0' << "\n";
    return;
  }
  int curr_row = max_index;
  int curr_col = seq2_count - 1;
  sequence[0] = seq1[curr_row];
  int pos = 1;
  while (dp[curr_row][curr_col] > 1) {
    if (curr_col > 0 && dp[curr_row][curr_col] == dp[curr_row][curr_col - 1]) {
      --curr_col;
    } else {
      for (int prev_row = curr_row - 1; prev_row >= 0; --prev_row) {
        if (seq1[prev_row] < seq1[curr_row] && dp[prev_row][curr_col] + 1 == dp[curr_row][curr_col]) {
          sequence[pos] = seq1[prev_row];
          curr_row = prev_row;
          pos++;
          break;
        }
      }
      if (curr_col > 0) {
        --curr_col;
      }
    }
  }
  std::cout << len << '\n';
  for (int i = len - 1; i >= 0; i--) {
    std::cout << sequence[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  int seq1_count = 0;
  int seq2_count = 0;
  int seq1[501];
  int seq2[501];
  std::cin >> seq1_count;
  for (int i = 0; i < seq1_count; i++) {
    int elem = 0;
    std::cin >> elem;
    seq1[i] = elem;
  }
  std::cin >> seq2_count;
  for (int i = 0; i < seq2_count; i++) {
    int elem = 0;
    std::cin >> elem;
    seq2[i] = elem;
  }
  LCIS(seq1, seq1_count, seq2, seq2_count);
  return 0;
}