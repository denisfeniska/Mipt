#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> graph;
  std::vector<bool> used;
  std::vector<std::pair<int, int>> bridges;
  std::vector<int> t_up;
  std::vector<int> height;

 public:
  void DFSFindBridges(int v, int parent = -1) {
    t_up[v] = height[v] = (parent == -1 ? 0 : height[parent] + 1);
    used[v] = true;
    for (auto& u: graph[v]) {
      if (u != parent) {
        if (used[u]) {
          t_up[v] = std::min(t_up[v], height[u]);
        } else {
          DFSFindBridges(u, v);
          t_up[v] = std::min(t_up[v], t_up[u]);
          if (t_up[u] > height[v]) {
            bridges.push_back({v, u});
          }
        }
      }
    }
  }
};