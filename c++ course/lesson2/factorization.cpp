#include <iostream>
#include <cmath>

int main() {
  int n = 0;
  std::cin >> n;
  while (n % 2 == 0) {
    std::cout << 2 << " ";
    n /= 2;
  }
  for (int i = 3; i <= sqrt(n); i += 2) {
    while (n % i == 0) {
      std::cout << i << " ";
      n /= i;
    }
  }
  if (n > 2) {
    std::cout << n << "\n";
  }
  return 0;
}