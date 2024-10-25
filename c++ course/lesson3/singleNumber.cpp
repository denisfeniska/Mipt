#include <iostream>

int main() {
  int nums[9999];
  for (int i = 0; i <= 9998; i++) {
    std::cin >> nums[i];
  }
  int unique = 0;
  for (int i = 0; i <= 9998; i++) {
    unique = unique ^ nums[i];
  }
  std::cout << unique << "\n";
  return 0;
}