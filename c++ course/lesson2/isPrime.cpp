#include <iostream>
#include <cmath>

int main() {
	int n = 0;
  std::cin >> n;
  if (n == 1) {
    std::cout << "NO" << "\n";
    return 0;
  }
  for (int i = 2; i <= sqrt(n); i++) {
  	if (n % i == 0) {
      std::cout << "NO" << "\n";
      return 0;
    }
  }
  std::cout << "YES" << "\n";
  return 0;
}