#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>

struct Edge {
  int to;
  int cap;
  int flow;
  int opposite;
};

class EdmondsKarp {
 public:
  int n_;
  std::vector<std::vector<Edge>> graph_;

  explicit EdmondsKarp(int v) : n_(v) {
    graph_.resize(n_ + 1);
  }

  bool BFS(int s, int ver, std::vector<int>& parent_vect, std::vector<int>& u_index) {
    std::vector<int> dist(graph_.size(), 1e9);
    dist[s] = 0;
    std::fill(parent_vect.begin(), parent_vect.end(), -1);
    parent_vect[s] = s;
    std::queue<int> queue;
    queue.push(s);
    while (!queue.empty() && parent_vect[ver] == -1) {
      int v = queue.front();
      queue.pop();
      for (int i = 0; i < static_cast<int>(graph_[v].size()); ++i) {
        Edge& e = graph_[v][i];
        if (dist[e.to] == 1e9 && e.cap > e.flow) {
          dist[e.to] = dist[v] + 1;
          parent_vect[e.to] = v;
          u_index[e.to] = i;
          queue.push(e.to);
        }
      }
    }
    return parent_vect[ver] != -1;
  }

  int MaxPathFlow(int s, int t) {
    int flow = 0;
    std::vector<int> parent_vect(n_ + 1, -1);
    std::vector<int> u_index(n_ + 1, -1);
    while (BFS(s, t, parent_vect, u_index)) {
      int path_flow = 1e9;
      for (int v = t; v != s; v = parent_vect[v]) {
        int u = parent_vect[v];
        int index = u_index[v];
        if (graph_[u][index].cap - graph_[u][index].flow < path_flow) {
          path_flow = graph_[u][index].cap - graph_[u][index].flow;
        }
      }
      for (int v = t; v != s; v = parent_vect[v]) {
        int u = parent_vect[v];
        int index = u_index[v];
        graph_[u][index].flow += path_flow;
        graph_[v][graph_[u][index].opposite].flow -= path_flow;
      }
      flow += path_flow;
    }
    return flow;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  EdmondsKarp ed_k(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int capacity = 0;
    std::cin >> u >> v >> capacity;
    ed_k.graph_[u].push_back({v, capacity, 0, static_cast<int>(ed_k.graph_[v].size())});
    ed_k.graph_[v].push_back({u, 0, 0, static_cast<int>(ed_k.graph_[u].size() - 1)});
  }
  std::cout << ed_k.MaxPathFlow(1, n) << "\n";
  return 0;
}