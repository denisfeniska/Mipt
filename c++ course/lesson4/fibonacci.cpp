#include <iostream>

int count = 0;

int Fibonacci(int n) {
  count++;
  if (n <= 2) {
    return 1;
  }
  return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main() {
  int n = 0;
  std::cin >> n;
  Fibonacci(n);
  std::cout << count << "\n";
  return 0;
}