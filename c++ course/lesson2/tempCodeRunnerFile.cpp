#include <iostream>
#include <cmath>

bool IsPrime(int n) {
  if (n == 1) {
    return false;
  }
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int n = 0;
  std::cin >> n;
  for (int i = 2; i <= sqrt(n); i++) {
    if ((n % i == 0) && IsPrime(i) && IsPrime(n / i)) {
      std::cout << "YES"
               << "\n";
      return 0;
    }
  }
  std::cout << "NO"
           << "\n";
  return 0;
}