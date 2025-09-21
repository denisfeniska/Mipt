#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int to;
  int weight;
};

std::vector<int> SPFA(std::vector<std::vector<Edge>>& graph, int s) {
  std::vector<int> dist(graph.size(), 1e9);
  std::vector<bool> in_queue(graph.size(), false);
  std::queue<int> queue;
  queue.push(s);
  in_queue[s] = true;
  dist[s] = 0;
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    in_queue[v] = false;
    for (auto& u : graph[v]) {
      if (dist[u.to] > dist[v] + u.weight) {
        dist[u.to] = dist[v] + u.weight;
        if (!in_queue[u.to]) {
          queue.push(u.to);
          in_queue[u.to] = true;
        }
      }
    }
  }
  return dist;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n);
  for (int i = 0; i < m; i++) {
    int from = 0;
    int to = 0;
    int weight = 0;
    std::cin >> from >> to >> weight;
    from--;
    to--;
    graph[from].push_back({to, weight});
  }
  std::vector<int> distances = SPFA(graph, 0);
  for (int i = 0; i < n; i++) {
    if (distances[i] == 1e9) {
      std::cout << 30000 << " ";
    } else {
      std::cout << distances[i] << " ";
    }
  }
  return 0;
}