#include <iostream>
#include <vector>
#include <cstdint>

struct Vertex {
  int64_t coord_x;
  int64_t coord_y;
};

int64_t ComputeVectorProduct(const Vertex& vertex_a, const Vertex& vertex_b, const Vertex& vertex_c) {
  int64_t delta_x1 = vertex_b.coord_x - vertex_a.coord_x;
  int64_t delta_y1 = vertex_b.coord_y - vertex_a.coord_y;
  int64_t delta_x2 = vertex_c.coord_x - vertex_b.coord_x;
  int64_t delta_y2 = vertex_c.coord_y - vertex_b.coord_y;
  return delta_x1 * delta_y2 - delta_y1 * delta_x2;
}

bool CheckRotationConsistency(const std::vector<Vertex>& shape) {
  int current_sign = 0;
  const size_t total_vertices = shape.size();
  auto get_next_index = [total_vertices](size_t base, int offset) { return (base + offset) % total_vertices; };
  auto determine_sign = [](int64_t value) { return (value > 0) ? 1 : ((value < 0) ? -1 : 0); };
  for (size_t idx = 0; idx < total_vertices; ++idx) {
    size_t next_idx = get_next_index(idx, 1);
    size_t nextnext_idx = get_next_index(idx, 2);
    int64_t product = ComputeVectorProduct(shape[idx], shape[next_idx], shape[nextnext_idx]);
    if (product == 0) {
      continue;
    }
    int product_sign = determine_sign(product);
    if (current_sign == 0) {
      current_sign = product_sign;
    } else if (current_sign != product_sign) {
      return false;
    }
  }
  return true;
}

bool IsPolygonConvex(const std::vector<Vertex>& shape) {
  return CheckRotationConsistency(shape);
}

std::vector<Vertex> InputVertices(int num_vertices) {
  std::vector<Vertex> shape_vertices(num_vertices);
  for (int idx = 0; idx < num_vertices; ++idx) {
    std::cin >> shape_vertices[idx].coord_x >> shape_vertices[idx].coord_y;
  }
  return shape_vertices;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Vertex> shape = InputVertices(n);
  std::cout << (IsPolygonConvex(shape) ? "YES\n" : "NO\n");
  return 0;
}