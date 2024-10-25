#include <iostream>

int Complement(int n) {
  int ones = 0;
  int temp = n;
  while (temp != 0) {
    ones = (ones << 1) | 1;
    temp = temp >> 1;
  }
  int res = n ^ ones;
  return res;
}

int main() {
  int n;
  std::cin >> n;
  int res = Complement(n);
  std::cout << res << "\n";
  return 0;
}
