#include <iostream>

template <class T>
void Reverse(T first, T last) {
  if (first == last) {
    return;
  }
  --last;
  while (first < last) {
    auto temp = *first;
    *first = *last;
    *last = temp;
    ++first;
    --last;
  }
}

void FillSequence(const std::string& first_sequence, const std::string& second_sequence, int** dp, size_t first_count,
                  size_t second_count) {
  for (size_t i = 1; i < first_count + 1; ++i) {
    for (size_t j = 1; j < second_count + 1; ++j) {
      if (first_sequence[i - 1] == second_sequence[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
}

int main() {
  std::string str = "0";
  std::cin >> str;
  std::string reverse_str = str;
  Reverse(reverse_str.begin(), reverse_str.end());
  int** dp = new int*[str.size() + 1];
  for (size_t i = 0; i < str.size() + 1; ++i) {
    dp[i] = new int[str.size() + 1];
    for (size_t j = 0; j < str.size() + 1; ++j) {
      dp[i][j] = 0;
    }
  }
  FillSequence(str, reverse_str, dp, str.size(), str.size());
  std::cout << str.size() - dp[str.size()][str.size()] << "\n";
  for (size_t i = 0; i < str.size() + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return 0;
}