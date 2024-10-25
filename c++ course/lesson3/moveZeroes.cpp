#include <iostream>

int main() {
  int nums[10000];
  for (int i = 0; i <= 9999; i++) {
    std::cin >> nums[i];
  }
  int zero_index = 0;
  for (int i = 0; i <= 9999; i++) {
    if (nums[i] != 0) {
      int temp = nums[i];
      nums[i] = nums[zero_index];
      nums[zero_index] = temp;
      zero_index++;
    }
  }
  for (int i = 0; i <= 9999; i++) {
    std::cout << nums[i] << " ";
  }
  return 0;
}