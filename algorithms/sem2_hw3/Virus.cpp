#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

struct Edge {
  int64_t to;
  int64_t weight;
};

std::vector<int64_t> SPFA(std::vector<std::vector<Edge>>& graph, int64_t s) {
  std::vector<int64_t> dist(graph.size(), 1e18);
  std::vector<bool> in_queue(graph.size(), false);
  std::queue<int64_t> queue;
  queue.push(s);
  in_queue[s] = true;
  dist[s] = 0;
  while (!queue.empty()) {
    int64_t v = queue.front();
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

std::vector<int64_t> NewSPFA(std::vector<std::vector<Edge>>& graph, const std::vector<int64_t>& s) {
  auto n = static_cast<int64_t>(graph.size());
  std::vector<int64_t> dist(n, 1e18);
  std::vector<bool> in_queue(n, false);
  std::queue<int64_t> queue;
  for (int64_t source : s) {
    dist[source] = 0;
    queue.push(source);
    in_queue[source] = true;
  }
  while (!queue.empty()) {
    int64_t v = queue.front();
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

int64_t GoodPath(std::vector<std::vector<Edge>>& graph, int64_t s, int64_t t, const std::vector<int64_t>& vir_vect) {
  auto n = static_cast<int64_t>(graph.size());
  std::vector<int64_t> dist(n, 1e18);
  std::vector<bool> in_queue(n, false);
  std::queue<int64_t> queue;
  dist[s] = 0;
  queue.push(s);
  in_queue[s] = true;
  while (!queue.empty()) {
    int64_t v = queue.front();
    queue.pop();
    in_queue[v] = false;
    for (auto& u : graph[v]) {
      if (dist[v] + u.weight < vir_vect[u.to] && dist[u.to] > dist[v] + u.weight) {
        dist[u.to] = dist[v] + u.weight;
        if (!in_queue[u.to]) {
          queue.push(u.to);
          in_queue[u.to] = true;
        }
      }
    }
  }
  return dist[t];
}

int main() {
  int64_t node_count = 0;
  int64_t connection_count = 0;
  int64_t infection_count = 0;
  std::cin >> node_count >> connection_count >> infection_count;
  std::vector<int64_t> vir_orig;
  vir_orig.reserve(infection_count);
  for (int64_t i = 0; i < infection_count; ++i) {
    int64_t infected_node = 0;
    std::cin >> infected_node;
    vir_orig.push_back(infected_node - 1);
  }
  std::vector<std::vector<Edge>> ship_map(node_count);
  for (int64_t edge_idx = 0; edge_idx < connection_count; ++edge_idx) {
    int64_t source = 0;
    int64_t destination = 0;
    int64_t travel_time = 0;
    std::cin >> source >> destination >> travel_time;
    --source;
    --destination;
    ship_map[source].push_back({destination, travel_time});
    ship_map[destination].push_back({source, travel_time});
  }
  int64_t player_position = 0;
  int64_t medical_room = 0;
  std::cin >> player_position >> medical_room;
  --player_position;
  --medical_room;
  auto vir_time = NewSPFA(ship_map, vir_orig);
  auto escape_time = GoodPath(ship_map, player_position, medical_room, vir_time);
  if (static_cast<double>(escape_time) == 1e18) {
    std::cout << -1;
  } else {
    std::cout << escape_time;
  }
  std::cout << "\n";
  return 0;
}