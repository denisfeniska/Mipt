#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdint>

struct Rectangle {
  int x1;
  int y1;
  int x2;
  int y2;
};

// struct correct_x_coords {
//   int x1;
//   int x2;
// };

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Rectangle> rectangles(n);
  std::set<int> x_coords;
  // std::vector<correct_x_coords> x_coords(N);
  for (int i = 0; i < n; ++i) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    rectangles[i] = {x1, y1, x2, y2};
    x_coords.insert(x1);
    x_coords.insert(x2);
  }
  std::vector<int> xs(x_coords.begin(), x_coords.end());
  int64_t res = 0;
  for (size_t i = 0; i < xs.size() - 1; ++i) {
    int x_prev = xs[i];
    int x_curr = xs[i + 1];
    int dx = x_curr - x_prev;
    if (dx == 0) {
      continue;
    }
    std::vector<std::pair<int, int>> y_coords;
    for (Rectangle& rect : rectangles) {
      if ((rect.x1 <= x_prev) && (rect.x2 >= x_curr)) {
        std::pair<int, int> new_pair = std::make_pair(rect.y1, rect.y2);
        y_coords.push_back(new_pair);
      }
    }
    if (y_coords.empty()) {
      continue;
    }
    std::sort(y_coords.begin(), y_coords.end());
    
    int curr_start = y_coords[0].first;
    int curr_end = y_coords[0].second;
    int64_t curr_len = 0;
    for (size_t j = 1; j < y_coords.size(); ++j) {
      int start = y_coords[j].first;
      int end = y_coords[j].second;
      if (start <= curr_end) {
        if (end >= curr_end) {
          curr_end = end;
        }
      } else {
        curr_len += curr_end - curr_start;
        curr_start = start;
        curr_end = end;
      }
    }
    curr_len += curr_end - curr_start;
    res += dx * curr_len;
  }
  std::cout << res << "\n";
  return 0;
}