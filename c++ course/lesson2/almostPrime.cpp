#include <iostream>
#include <cmath>

int main() {
  int n = 0;
  std::cin >> n;
  int cnt = 0;
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0 && i * i != n) {
      cnt += 2;
    } else if (n % i == 0 && i * i == n) {
      cnt += 1;
    }
  }
  if (cnt == 2) {
    std::cout << "YES" 
              << "\n";
  } else {
    std::cout << "NO" 
              << "\n";
  }
  return 0;
}