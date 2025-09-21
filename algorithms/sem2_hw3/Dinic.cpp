#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge {
  int to;
  int cap;
  int opposite;
};

class Dinic {
 private:
  int n_;
  std::vector<int> step_;
  std::vector<int> better_;

  bool BFS(int s, int t) {
    std::vector<int> dist(n_, 1e9);
    dist[s] = 0;
    std::queue<int> queue;
    queue.push(s);
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (Edge& e : graph[v]) {
        if (dist[e.to] == 1e9 && e.cap > 0) {
          dist[e.to] = dist[v] + 1;
          queue.push(e.to);
        }
      }
    }
    step_ = dist;
    return dist[t] != 1e9;
  }

  int DFS(int v, int t, int flow, std::vector<std::string>& color) {
    if (v == t || flow == 0) {
      return flow;
    }
    color[v] = "grey";
    for (int& i = better_[v]; i < static_cast<int>(graph[v].size()); ++i) {
      Edge& e = graph[v][i];
      if (step_[e.to] == step_[v] + 1 && e.cap > 0 && color[e.to] == "white") {
        int new_v = DFS(e.to, t, (flow < e.cap) ? flow : e.cap, color);
        if (new_v > 0) {
          e.cap -= new_v;
          graph[e.to][e.opposite].cap += new_v;
          color[v] = "black";
          return new_v;
        }
      }
    }
    color[v] = "black";
    return 0;
  }

 public:
  std::vector<std::vector<Edge>> graph;

  explicit Dinic(int vertices) : n_(vertices) {
    graph.resize(n_);
    step_.resize(n_);
    better_.resize(n_);
  }

  int MaxPathFlow(int s, int t) {
    int flow = 0;
    std::vector<std::string> color;
    while (BFS(s, t)) {
      better_.assign(n_, 0);
      color.assign(n_, "white");
      while (int new_v = DFS(s, t, 1e9, color)) {
        flow += new_v;
        color.assign(n_, "white");
      }
    }
    return flow;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Dinic algo(n + 1);
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    int capacity = 0;
    std::cin >> from >> to >> capacity;
    algo.graph[from].push_back({to, capacity, static_cast<int>(algo.graph[to].size())});
    algo.graph[to].push_back({from, 0, static_cast<int>(algo.graph[from].size())});
  }
  std::cout << algo.MaxPathFlow(1, n) << "\n";
  return 0;
}