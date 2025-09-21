#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> graph;
  std::vector<bool> used;
  std::vector<int> points;
  std::vector<int> t_up;
  std::vector<int> height;

 public:
  void DFSFindPoints(int v, int parent = -1) {
    t_up[v] = height[v] = (parent == -1 ? 0 : height[parent] + 1);
    used[v] = true;
    int children = 0;
    for (auto& u: graph[v]) {
      if (u != parent) {
        if (used[u]) {
          t_up[v] = std::min(t_up[v], height[u]);
        } else {
          DFSFindPoints(u, v);
          ++children;
          t_up[v] = std::min(t_up[v], t_up[u]);
          if (t_up[u] >= height[v]) {
            points.push_back(v);
          }
        }
      }
    }
    if (parent == -1 and children > 1) {
      points.push_back(v);
    }
  }
};