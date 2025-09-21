#include <iostream>
#include <vector>
#include <queue>

struct edge {
  int from;
  int to;
};

std::vector<int> BFS(std::vector<std::vector<edge>> graph, int s) {
  std::vector<int> dist(graph.size(), 10^9);
  dist[s] = 0;
  std::queue<int> queue; // std::deque
  queue.push(s);
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    for (auto& e : graph[v]) {
      if (dist[e.to] != 10^9) { // if (dist[e.to] > dist[v + e.weight])
        dist[e.to] = dist[v] + 1; // if (e.weight == 0) { dequeu.push_front(e); } else { deque.push_back(e); } dist[e.to] == int[v] + e.weight;
        queue.push(e.to);
      }
    }
  }
  return dist;
}