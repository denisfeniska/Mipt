#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge {
  int to;
  int weight;
  Edge(int to, int weight) : to(to), weight(weight) {
  }
};

std::vector<int> SPFAStepsLimit(const std::vector<std::vector<Edge>>& graph, int s, int f, int k) {
  int n = static_cast<int>(graph.size());
  std::vector<int> curr(n, 1e9);
  std::vector<int> next(n, 1e9);
  std::vector<int> results(k + 1, 1e9);
  curr[s] = 0;
  for (int step = 1; step <= k; ++step) {
    std::fill(next.begin(), next.end(), 1e9);
    std::queue<int> queue;
    std::vector<bool> in_queue(n, false);
    for (int v = 0; v < n; ++v) {
      if (curr[v] != 1e9) {
        queue.push(v);
        in_queue[v] = true;
      }
    }
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      in_queue[v] = false;
      if (curr[v] == 1e9) {
        continue;
      }
      for (const auto& u : graph[v]) {
        int to = u.to;
        int new_dist = curr[v] + u.weight;
        if (new_dist < next[to]) {
          next[to] = new_dist;
          if (!in_queue[to]) {
            queue.push(to);
            in_queue[to] = true;
          }
        }
      }
    }
    results[step] = next[f];
    curr.swap(next);
  }
  return results;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int k = 0;
  int s = 0;
  int f = 0;
  std::cin >> n >> m >> k >> s >> f;
  s--;
  f--;
  std::vector<std::vector<int>> min_edge_cost(n, std::vector<int>(n, 1e9));
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    int cost = 0;
    std::cin >> from >> to >> cost;
    from--;
    to--;
    if (cost < min_edge_cost[from][to]) {
      min_edge_cost[from][to] = cost;
    }
  }
  std::vector<std::vector<Edge>> graph(n);
  for (int from = 0; from < n; ++from) {
    for (int to = 0; to < n; ++to) {
      if (min_edge_cost[from][to] != 1e9) {
        graph[from].emplace_back(to, min_edge_cost[from][to]);
      }
    }
  }
  auto results = SPFAStepsLimit(graph, s, f, k);
  int min_cost = 1e9;
  for (int i = 1; i <= k; ++i) {
    min_cost = std::min(min_cost, results[i]);
  }
  if (min_cost == 1e9) {
    std::cout << -1 << std::endl;
  } else {
    std::cout << min_cost << std::endl;
  }
  return 0;
}