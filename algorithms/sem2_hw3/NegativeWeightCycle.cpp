#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int to;
  int weight;
};

bool IsCycleNegative(std::vector<std::vector<Edge>>& graph, std::vector<int>& cycle) {
  int n = static_cast<int>(graph.size());
  std::vector<int> dist(n, 0);
  std::vector<int> parent(n, 0);
  std::vector<int> count(n, 0);
  std::vector<bool> in_queue(n, false);
  std::queue<int> queue;
  for (int i = 0; i < n; ++i) {
    queue.push(i);
    in_queue[i] = true;
  }
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    in_queue[v] = false;
    for (auto& u : graph[v]) {
      if (dist[u.to] > dist[v] + u.weight) {
        dist[u.to] = dist[v] + u.weight;
        parent[u.to] = v;
        count[u.to]++;
        if (count[u.to] >= n) {
          int first = u.to;
          for (int i = 0; i < n; ++i) {
            first = parent[first];
          }
          int curr = first;
          cycle.push_back(curr);
          curr = parent[curr];
          while (curr != first) {
            cycle.push_back(curr);
            curr = parent[curr];
          }
          cycle.push_back(first);
          return true;
        }
        if (!in_queue[u.to]) {
          queue.push(u.to);
          in_queue[u.to] = true;
        }
      }
    }
  }
  return false;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<Edge>> graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (weight != 100000) {
        graph[i].push_back({j, weight});
      }
    }
  }
  std::vector<int> cycle;
  if (IsCycleNegative(graph, cycle)) {
    std::cout << "YES"
              << "\n";
    int cycle_size = static_cast<int>(cycle.size());
    std::cout << cycle_size << "\n";
    for (int i = cycle_size - 1; i >= 0; --i) {
      std::cout << cycle[i] + 1 << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  return 0;
}