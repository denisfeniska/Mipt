#include <iostream>

bool CheckPosition(__INT64_TYPE__ w, __INT64_TYPE__ h, __INT64_TYPE__ n, __INT64_TYPE__ len) {
  __INT64_TYPE__ x_photos = len / w;
  __INT64_TYPE__ y_photos = len / h;
  if (x_photos > n) {
    x_photos = n;
  }
  if (y_photos > n) {
    y_photos = n;
  }
  __INT64_TYPE__ photos = x_photos * y_photos;
  return photos >= n;
}

int main() {
  __INT64_TYPE__ w = 0;
  __INT64_TYPE__ h = 0;
  __INT64_TYPE__ n = 0;
  std::cin >> w >> h >> n;
  __INT64_TYPE__ start = 1;
  __INT64_TYPE__ end = 0;
  if (w >= h) {
    end = w * n;
  } else {
    end = h * n;
  }
  while (start < end) {
    __INT64_TYPE__ mid = start + (end - start) / 2;
    if (CheckPosition(w, h, n, mid)) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  std::cout << start << "\n";
  return 0;
}