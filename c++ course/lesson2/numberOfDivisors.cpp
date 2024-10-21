#include <iostream>
#include <cmath>

int main() {
  int n = 0;
  int count = 0;
  std::cin >> n;
  if (n == 1) {
    std::cout << 1 << "\n";
    return 0;
  }
  for (int i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {
      count += 2;
      if (i == n / i) {
        count--;
      }
    }
  }
  std::cout << count << "\n";
  return 0;
}