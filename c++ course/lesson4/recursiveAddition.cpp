#include <iostream>

int Sum(int a, int b, int sum) {
  if (b == 0) {
    return sum;
  }
  sum += 1;
  b -= 1;
  return Sum(a, b, sum);
}

int main() {
  int a = 0;
  int b = 0;
  std::cin >> a;
  std::cin >> b;
  std::cout << Sum(a, b, a) << "\n";
  return 0;
}