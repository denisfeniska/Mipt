#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

struct Edge {
  int64_t to;
  int64_t time_dep;
  int64_t time_arr;
};

std::vector<int64_t> SPFA(std::vector<std::vector<Edge>>& graph, int64_t s, int64_t n) {
  std::vector<int64_t> dist(n + 1, 1e18);
  std::vector<bool> in_queue(n + 1, false);
  std::queue<int64_t> queue;
  queue.push(s);
  in_queue[s] = true;
  dist[s] = 0;
  while (!queue.empty()) {
    int64_t v = queue.front();
    queue.pop();
    in_queue[v] = false;
    for (auto& edge : graph[v]) {
      if (dist[v] <= edge.time_dep) {
        if (dist[edge.to] > edge.time_arr) {
          dist[edge.to] = edge.time_arr;
          if (!in_queue[edge.to]) {
            queue.push(edge.to);
            in_queue[edge.to] = true;
          }
        }
      }
    }
  }
  return dist;
}

int main() {
  int64_t n = 0;
  int64_t a = 0;
  int64_t b = 0;
  int64_t k = 0;
  std::cin >> n;
  std::cin >> a;
  std::cin >> b;
  std::cin >> k;
  std::vector<std::vector<Edge>> graph;
  graph.resize(n + 1);
  for (int64_t i = 0; i < k; i++) {
    int64_t from = 0;
    int to = 0;
    int64_t departure = 0;
    int64_t arrival = 0;
    std::cin >> from;
    std::cin >> departure;
    std::cin >> to;
    std::cin >> arrival;
    Edge new_edge = {to, departure, arrival};
    graph[from].push_back(new_edge);
  }
  auto min_time_arr = SPFA(graph, a, n);
  std::cout << min_time_arr[b] << std::endl;
  return 0;
}