#include <iostream>
#include <vector>
#include <queue>

struct edge {
  int from;
  int to;
  int weight;
};

std::vector<int> BFS(std::vector<std::vector<edge>> graph, int k, int s) {
  std::vector<int> dist(graph.size(), 10^9);
  dist[s] = 0;
  std::vector<std::queue<int>> queues(k + 1);
  queues[0].push(s);
  int len = 0;
  int count = 1;
  while (count != 0) {
    while (!queues[len % (k + 1)].empty()) {
      int v = queues[len % (k + 1)].front();
      queues[len % (k + 1)].pop();
      --count;
      for (auto& e: graph[v]) {
        if (dist[e.to] > dist[v] + e.weight) {
          dist[e.to] = dist[v] + e.weight;
          queues[(len + e.weight) % (k + 1)].push(e.to);
          ++count;
        }
      }
    }
    ++len;
  }
  return dist;
}