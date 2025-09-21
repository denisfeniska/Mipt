#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// картчайшие пути между всеми парами вершин

// matrix устроен так: на диагонали (0, 0), где есть ребро - вес, где нет ребра - бесконечности

std::vector<std::vector<int>> Floyd(std::vector<std::vector<int>>& matrix) {
  std::vector<std::vector<int>> dist = matrix;
  int n = matrix.size() + 1;
  std::vector<std::vector<int>> parent(n, std::vector<int>(n));
  for (int i = 1; i < n; ++i) {
    for (int v = 1; v < n; ++v) {
      for (int u = 1; u < n; ++u) {
        if (dist[v][u] > dist[v][i] + dist[i][u]) {
          dist[v][u] = dist[v][i] + dist[i][u];
          parent[v][u] = i;
        }
      }
    }
  }
  return dist;
}