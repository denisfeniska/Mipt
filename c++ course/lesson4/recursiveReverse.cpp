#include <iostream>

void Reverse(int n) {
  if (n == 0) {
    return;
  }
  int el = 0;
  std::cin >> el;
  Reverse(n - 1);
  std::cout << el << " ";
}

int main() {
  int n = 0;
  std::cin >> n;
  Reverse(n);
  return 0;
}