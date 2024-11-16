#include <iostream>

bool CheckPosition(int* desk_rows, int x, int y) {
  for (int i = 0; i < x; ++i) {
    if (desk_rows[i] == y) {
      return false;
    }
    if (desk_rows[i] - y == x - i || y - desk_rows[i] == x - i) {
      return false;
    }
  }
  return true;
}

void PushQueens(int n, int* desk_rows, int x, int& res_count) {
  if (x == n) {
    res_count++;
    return;
  }
  for (int y = 0; y < n; ++y) {
    if (CheckPosition(desk_rows, x, y)) {
      desk_rows[x] = y;
      PushQueens(n, desk_rows, x + 1, res_count);
    }
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  int* desk_rows = new int[n];
  int res_count = 0;
  PushQueens(n, desk_rows, 0, res_count);
  std::cout << res_count << "\n";
  delete[] desk_rows;
  return 0;
}