#include <iostream>

int Exponentiation(int a, int n, int res) {
  if (n == 0) {
    return res;
  }
  if (n % 2 == 1) {
    res *= a;
    n -= 1;
  }
  return Exponentiation(a * a, n / 2, res);
}

int main() {
  int a = 0;
  int n = 0;
  std::cin >> a;
  std::cin >> n;
  std::cout << Exponentiation(a, n, 1) << "\n";
  return 0;
}