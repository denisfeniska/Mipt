#include <iostream>

int main() {
  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m >> k;
  int* color_count = new int[k]();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int color = (i + j) % k;
      color_count[color]++;
    }
  }
  for (int color = 0; color < k; ++color) {
    std::cout << color_count[color] << " ";
  }
  std::cout << "\n";
  delete[] color_count;
  return 0;
}
