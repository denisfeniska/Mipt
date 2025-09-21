#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int final_vertex;
  int edge_number;

  Edge(int t, int i) : final_vertex(t), edge_number(i) {
  }
};

class Graph {
 private:
  std::vector<std::vector<Edge>> graph_;
  std::vector<bool> used_;
  std::vector<int> bridges_;
  std::vector<int> t_up_;
  std::vector<int> height_;
  bool is_bridges_found_;

 public:
  explicit Graph(int n) : graph_(n + 1), used_(n + 1, false), t_up_(n + 1), height_(n + 1), is_bridges_found_(false) {
  }

  void AddEdge(int u, int v, int id) {
    graph_[u].emplace_back(v, id);
    graph_[v].emplace_back(u, id);
  }

  void DFSFindBridges(int v, int parent = -1) {
    used_[v] = true;
    t_up_[v] = height_[v] = (parent == -1 ? 0 : height_[parent] + 1);
    for (auto& edge : graph_[v]) {
      int u = edge.final_vertex;
      int edge_id = edge.edge_number;
      if (u == parent) {
        continue;
      }
      if (used_[u]) {
        t_up_[v] = std::min(height_[u], t_up_[v]);
      } else {
        DFSFindBridges(u, v);
        t_up_[v] = std::min(t_up_[u], t_up_[v]);
        if (t_up_[u] > height_[v]) {
          bridges_.push_back(edge_id);
        }
      }
    }
  }

  const std::vector<int>& GetBridges() {
    if (!is_bridges_found_) {
      fill(used_.begin(), used_.end(), false);
      bridges_.clear();
      for (size_t v = 1; v < graph_.size(); ++v) {
        if (!used_[v]) {
          DFSFindBridges(static_cast<int>(v));
        }
      }
      is_bridges_found_ = true;
    }
    return bridges_;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph g(n);

  for (int i = 1; i <= m; ++i) {
    int u = 0;
    int v = 0;
    std::cin >> u >> v;
    g.AddEdge(u, v, i);
  }

  std::vector<int> bridges = g.GetBridges();
  std::sort(bridges.begin(), bridges.end());

  std::cout << bridges.size() << '\n';
  for (size_t i = 0; i < bridges.size(); ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << bridges[i];
  }
  std::cout << '\n';
  return 0;
}