#include <iostream>
#include <cmath>

int IsPrime(int n) {
  if (n <= 1) {
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
  int a = 0;
  int b = 0;
  std::cin >> a;
  std::cin >> b;
  for (int num = a; num <= b; num++) {
    if (IsPrime(num)) {
      std::cout << num << "\n";
    }
  }
  return 0;
}