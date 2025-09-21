#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge {
  int to;
  int weight;
};

std::vector<int> SPFA(const std::vector<std::vector<Edge>>& graph, int s, int n) {
  std::vector<int> dist(n + 1, 1e9);
  std::vector<bool> in_queue(n + 1, false);
  std::queue<int> q;
  dist[s] = 0;
  q.push(s);
  in_queue[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    in_queue[u] = false;
    for (const auto& edge : graph[u]) {
      int v = edge.to;
      int weight = edge.weight;
      if (dist[u] != 1e9 && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        if (!in_queue[v]) {
          q.push(v);
          in_queue[v] = true;
        }
      }
    }
  }
  return dist;
}

std::vector<int> Dijkstra(const std::vector<std::vector<Edge>>& graph, int s, int n) {
  std::vector<int> dist(n, 1e9);
  dist[s] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
  pq.emplace(0, s);
  while (!pq.empty()) {
    int d = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (d > dist[u]) {
      continue;
    }
    for (auto& edge : graph[u]) {
      int v = edge.to;
      int weight = edge.weight;
      if (dist[u] != 1e9 && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
      }
    }
  }
  return dist;
}

std::vector<std::vector<int>> Johnson(const std::vector<std::vector<Edge>>& graph, int n) {
  std::vector<std::vector<Edge>> new_graph(n + 1);
  for (int i = 0; i < n; ++i) {
    new_graph[i] = graph[i];
  }
  for (int i = 0; i < n; ++i) {
    new_graph[n].push_back({i, 0});
  }
  std::vector<int> h = SPFA(new_graph, n, n);
  std::vector<std::vector<Edge>> pos_graph(n);
  for (int u = 0; u < n; ++u) {
    for (auto& edge : graph[u]) {
      int v = edge.to;
      int weight = edge.weight;
      pos_graph[u].push_back({v, weight + h[u] - h[v]});
    }
  }
  std::vector<std::vector<int>> paths(n, std::vector<int>(n, 1e9));
  for (int i = 0; i < n; ++i) {
    std::vector<int> dist = Dijkstra(pos_graph, i, n);
    for (int j = 0; j < n; ++j) {
      if (dist[j] != 1e9) {
        paths[i][j] = dist[j] + h[j] - h[i];
      }
    }
  }
  return paths;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n);
  for (int i = 0; i < m; ++i) {
    int a = 0;
    int b = 0;
    int w = 0;
    std::cin >> a >> b >> w;
    graph[a].push_back({b, w});
  }

  std::vector<std::vector<int>> paths = Johnson(graph, n);

  int max_dis = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && paths[i][j] != 1e9) {
        max_dis = std::max(max_dis, paths[i][j]);
      }
    }
  }
  std::cout << max_dis << "\n";
  return 0;
}