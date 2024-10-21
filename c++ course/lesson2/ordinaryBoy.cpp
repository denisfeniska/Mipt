#include <iostream>

int main() {
  int x = 0;
  std::cin >> x;
  if (x >= 100 * 45360) {
    std::cout << (x / 45360 + 1) * 45360;
  } else {
    bool flag = false;
    for (int y = x; 100 * y <= 101 * x; ++y) {
      int cnt = 0;
      for (int i = 1; i * i <= y; ++i) {
        if (y % i == 0) {
          if (i * i == y) {
            cnt += 1;
          } else {
            cnt += 2;
          }
          if (cnt >= 100) {
            break;
          }
        }
      }
      if (cnt >= 100) {
        std::cout << y;
        flag = true;
        break;
      }
    }
    if (flag == false) {
      std::cout << -1 << "\n";
    }
  }
  return 0;
}
