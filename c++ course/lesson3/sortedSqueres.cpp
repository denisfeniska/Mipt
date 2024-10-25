#include <iostream>

int main() {
  int nums[10000];
  for (int i = 0; i <= 9999; i++) {
    std::cin >> nums[i];
  }
  int res_arr[10000];
  int start = 0;
  int end = 10000 - 1;
  int res_index = 10000 - 1;
  while (start <= end) {
    int start_square = nums[start] * nums[start];
    int end_square = nums[end] * nums[end];
    if (start_square > end_square) {
      res_arr[res_index] = start_square;
      start++;
    } else {
      res_arr[res_index] = end_square;
      end--;
    }
    res_index--;
  }
  for (int i = 0; i <= 9999; i++) {
    std::cout << res_arr[i] << " ";
  }
  return 0;
}