#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int count = 0;
  for (int x = 0; x * (x + 1) <= n; x++) {
    if ((n - x) % (x + 1) == 0) {
      int y = (n - x) / (x + 1);
      if (y >= x) {
        count += (x == y) ? 1 : 2;
      }
    }
  }
  std::cout << count << "\n";
  return 0;
}