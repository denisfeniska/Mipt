#include <iostream>

double Exponentiation(double a, int n) {
  if (n == 0) {
    return 1;
  }
  double half = Exponentiation(a, n / 2);
  if (n % 2 == 0) {
    return half * half;
  }
  return a * half * half;
}

int main() {
  double a = 0;
  int n = 0;
  std::cin >> a;
  std::cin >> n;
  std::cout << Exponentiation(a, n) << "\n";
  return 0;
}