#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

struct Edge {
  int64_t to;
  int64_t weight;
};

std::vector<int64_t> SPFA(const std::vector<std::vector<Edge>>& graph, int64_t s) {
  auto n = static_cast<int64_t>(graph.size());
  std::vector<int64_t> dist(n, 1e18 / 2);
  std::vector<bool> in_queue(n, false);
  std::queue<int64_t> queue;
  queue.push(s);
  in_queue[s] = true;
  dist[s] = 0;
  while (!queue.empty()) {
    int64_t v = queue.front();
    queue.pop();
    in_queue[v] = false;
    for (auto& u : graph[v]) {
      if (static_cast<double>(dist[v]) != 1e18 / 2 && dist[u.to] > dist[v] + u.weight) {
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
  int64_t number = 0;
  int64_t up = 0;
  int64_t down = 0;
  int64_t in_cost = 0;
  int64_t out_cost = 0;
  int64_t telep_number = 0;
  std::cin >> number >> up >> down >> in_cost >> out_cost >> telep_number;
  std::vector<std::vector<Edge>> graph(number + 1);
  for (int64_t i = 1; i <= number; ++i) {
    if (i < number) {
      Edge e;
      e.to = i + 1;
      e.weight = up;
      graph[i].push_back(e);
    }
    if (i > 1) {
      Edge e;
      e.to = i - 1;
      e.weight = down;
      graph[i].push_back(e);
    }
  }
  for (int64_t i = 0; i < telep_number; ++i) {
    int64_t palub_num = 0;
    std::cin >> palub_num;
    std::vector<int64_t> telep_f(palub_num);
    for (int64_t j = 0; j < palub_num; ++j) {
      std::cin >> telep_f[j];
    }
    for (int64_t j = 0; j < palub_num; ++j) {
      int64_t from_floor = telep_f[j];
      if (from_floor < 1 || from_floor > number) {
        continue;
      }
      for (int64_t k = 0; k < palub_num; ++k) {
        if (j == k) {
          continue;
        }
        int64_t to_floor = telep_f[k];
        if (to_floor < 1 || to_floor > number) {
          continue;
        }
        Edge teleport_edge;
        teleport_edge.to = to_floor;
        teleport_edge.weight = in_cost + out_cost;
        graph[from_floor].push_back(teleport_edge);
      }
    }
  }
  std::vector<int64_t> distances = SPFA(graph, 1);
  if (static_cast<double>(distances[number]) == 1e18 / 2) {
    std::cout << "-1"
              << "\n";
  } else {
    std::cout << distances[number] << "\n";
  }
  return 0;
}