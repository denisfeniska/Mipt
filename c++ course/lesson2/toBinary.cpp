#include <iostream>
#include <string>

int main() {
  int n = 0;
  std::cin >> n;
  if (n == 0) {
    return 0;
  }
  std::string str;
  while (n != 0) {
    str = std::to_string(n % 2) + str;
    n /= 2;
  }
  std::cout << str << "\n";
  return 0;
}