#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>

struct Point2D {
  int64_t x;
  int64_t y;
};

auto ReadPolygon(int sides) {
  std::vector<Point2D> shape(sides);
  auto read_coord = [](auto& input) {
    Point2D pt;
    input >> pt.x >> pt.y;
    return pt;
  };
  for (int i = 0; i < sides; ++i) {
    shape[i] = read_coord(std::cin);
  }
  return shape;
}

long double ComputeSurface(const std::vector<Point2D>& figure) {
  auto cross_product = [](const Point2D& a, const Point2D& b) { return a.x * b.y - a.y * b.x; };
  int64_t accumulator = 0;
  const size_t len = figure.size();
  for (size_t idx = 0; idx < len; ++idx) {
    size_t next_idx = (idx + 1) % len;
    accumulator += cross_product(figure[idx], figure[next_idx]);
  }
  return (accumulator < 0 ? -accumulator : accumulator) * 0.5L;
}

int main() {
  int sides = 0;
  std::cin >> sides;
  const auto figure = ReadPolygon(sides);
  const long double surface = ComputeSurface(figure);
  std::printf("%.1Lf\n", surface);
  return 0;
}