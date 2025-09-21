#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  std::vector<bool> used_;
  std::vector<bool> is_point_soch_;
  std::vector<int> t_up_;
  std::vector<int> height_;

 public:
  explicit Graph(int n) : graph_(n), used_(n, false), is_point_soch_(n, false), t_up_(n, 0), height_(n, 0) {
  }

  void AddEdge(int u, int v) {
    graph_[u].push_back(v);
    graph_[v].push_back(u);
  }

  void DFSFindPoints(int v, int parent = -1) {
    used_[v] = true;
    height_[v] = (parent == -1 ? 0 : height_[parent] + 1);
    t_up_[v] = height_[v];
    int children = 0;
    for (int u : graph_[v]) {
      if (used_[u]) {
        t_up_[v] = std::min(t_up_[v], height_[u]);
      } else {
        children++;
        DFSFindPoints(u, v);
        t_up_[v] = std::min(t_up_[v], t_up_[u]);
        if (parent != -1 && t_up_[u] >= height_[v]) {
          is_point_soch_[v] = true;
        }
      }
    }
    if (parent == -1 && children > 1) {
      is_point_soch_[v] = true;
    }
  }

  bool IsPointSoch(int v) {
    return is_point_soch_[v];
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph g(n + m);

  for (int i = 0; i < m; i++) {
    int a = 0;
    int b = 0;
    int c = 0;
    std::cin >> a >> b >> c;
    a--;
    b--;
    c--;
    g.AddEdge(n + i, a);
    g.AddEdge(n + i, b);
    g.AddEdge(n + i, c);
  }

  g.DFSFindPoints(n, -1);

  std::vector<int> critical_p;
  for (int i = 0; i < m; i++) {
    int node = n + i;
    if (g.IsPointSoch(node)) {
      critical_p.push_back(i + 1);
    }
  }

  std::cout << critical_p.size() << "\n";
  for (int num : critical_p) {
    std::cout << num << " ";
  }
  std::cout << "\n";
  return 0;
}