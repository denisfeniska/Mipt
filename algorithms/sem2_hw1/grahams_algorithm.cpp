#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
  int64_t x;
  int64_t y;
  Point() : x(0), y(0) {
  }
  Point(int64_t x, int64_t y) : x(x), y(y) {
  }
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool operator<(const Point& other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};

int64_t VectorProduct(const Point& first, const Point& second, const Point& third) {
  return (second.x - first.x) * (third.y - second.y) - (second.y - first.y) * (third.x - second.x);
}

bool IsEqual(const Point& first, const Point& second) {
  return first.x == second.x && first.y == second.y;
}

std::vector<Point> RemoveSamePoints(std::vector<Point> points_arr) {
  std::sort(points_arr.begin(), points_arr.end());
  auto duplicates_begin = std::unique(points_arr.begin(), points_arr.end(), IsEqual);
  points_arr.erase(duplicates_begin, points_arr.end());
  return points_arr;
}

Point FirstPoint(const std::vector<Point>& points_arr) {
  Point first = points_arr[0];
  for (const auto& point : points_arr) {
    if (point.x < first.x || (point.x == first.x && point.y < first.y)) {
      first = point;
    }
  }
  return first;
}

struct PointComparator {
  Point first;
  explicit PointComparator(const Point& first) : first(first) {
  }
  bool operator()(const Point& a, const Point& b) const {
    int64_t comp = VectorProduct(first, a, b);
    if (comp != 0) {
      return comp > 0;
    }
    int64_t dist_a = (a.x - first.x) * (a.x - first.x) + (a.y - first.y) * (a.y - first.y);
    int64_t dist_b = (b.x - first.x) * (b.x - first.x) + (b.y - first.y) * (b.y - first.y);
    return dist_a < dist_b;
  }
};

std::vector<Point> SortAngles(const std::vector<Point>& points_arr, const Point& first) {
  std::vector<Point> res_sorted;
  for (const auto& point : points_arr) {
    if (!(point == first)) {
      res_sorted.push_back(point);
    }
  }
  std::sort(res_sorted.begin(), res_sorted.end(), PointComparator(first));
  return res_sorted;
}

std::vector<Point> SorterOnLine(std::vector<Point> res_sorted, const Point& first) {
  std::vector<Point> sorted;
  for (auto& point : res_sorted) {
    while (!sorted.empty() && VectorProduct(first, sorted.back(), point) == 0) {
      int64_t dist_point = (point.x - first.x) * (point.x - first.x) + (point.y - first.y) * (point.y - first.y);
      int64_t dist_last = (sorted.back().x - first.x) * (sorted.back().x - first.x) +
                          (sorted.back().y - first.y) * (sorted.back().y - first.y);
      if (dist_point > dist_last) {
        sorted.pop_back();
      } else {
        break;
      }
    }
    sorted.push_back(point);
  }
  return sorted;
}

std::vector<Point> Shell(std::vector<Point>& sorted, Point& first) {
  std::vector<Point> shell = {first};
  for (auto& point : sorted) {
    while (shell.size() >= 2) {
      const Point& a = shell[shell.size() - 2];
      const Point& b = shell.back();
      if (VectorProduct(a, b, point) <= 0) {
        shell.pop_back();
      } else {
        break;
      }
    }
    shell.push_back(point);
  }
  if (shell.size() >= 3) {
    const Point& a = shell[shell.size() - 2];
    const Point& b = shell.back();
    if (VectorProduct(shell[0], a, b) == 0) {
      shell.pop_back();
    }
  }
  std::reverse(shell.begin() + 1, shell.end());
  return shell;
}

void RemovePoints(std::vector<Point>& shell) {
  bool flag = true;
  while (flag && shell.size() >= 3) {
    flag = false;
    for (size_t i = 0; i < shell.size(); ++i) {
      size_t j = (i + 1) % shell.size();
      size_t k = (i + 2) % shell.size();
      if (VectorProduct(shell[i], shell[j], shell[k]) == 0) {
        shell.erase(shell.begin() + static_cast<std::ptrdiff_t>(j));
        flag = true;
        break;
      }
    }
  }
}

long double Area(std::vector<Point>& shell) {
  int64_t area = 0;
  for (size_t i = 0; i < shell.size(); ++i) {
    size_t j = (i + 1) % shell.size();
    area += shell[i].x * shell[j].y - shell[j].x * shell[i].y;
  }
  return std::abs(static_cast<long double>(area)) / 2.0L;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Point> points_arr(n);
  for (auto& point : points_arr) {
    std::cin >> point.x >> point.y;
  }
  points_arr = RemoveSamePoints(points_arr);
  if (points_arr.size() < 3) {
    std::cout << "0\n";
    return 0;
  }
  Point first = FirstPoint(points_arr);
  std::vector<Point> sorted = SortAngles(points_arr, first);
  std::vector<Point> filtered = SorterOnLine(sorted, first);
  std::vector<Point> shell = Shell(filtered, first);
  RemovePoints(shell);
  if (shell.size() < 3) {
    std::cout << "0\n";
    return 0;
  }
  std::cout << shell.size() << "\n";
  for (const auto& p : shell) {
    std::cout << p.x << " " << p.y << "\n";
  }
  long double area = Area(shell);
  area = std::roundl(area * 10.0L) / 10.0L;
  std::cout << std::fixed;
  std::cout.precision(1);
  std::cout << area << "\n";
  return 0;
}