#include <iostream>
#include <vector>
#include <queue>

// расстояния от одной вершины до всех остлаьных

struct Edge {
  int to;
  int weight;
};

std::vector<int> SPFA(std::vector<std::vector<Edge>>& graph, int s) {
  std::vector<int> dist(graph.size(), 1e9);
  std::vector<bool> in_queue(graph.size(), false);
  std::queue<int> queue;
  queue.push(s);
  in_queue[s] = 0;
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
}