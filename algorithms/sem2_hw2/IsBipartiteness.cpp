#include <iostream>
#include <vector>
#include <queue>
#include <string>

struct Edge {
  int from;
  int to;
};

bool IsBipartitenessnessBFS(std::vector<std::vector<Edge>> graph, int s, std::vector<std::string>& color) {
  std::queue<int> queue;
  queue.push(s);
  color[s] = "grey";
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    for (auto& e : graph[v]) {
      if (color[e.to] == "white") {
        color[e.to] = (color[v] == "grey") ? "black" : "grey";
        queue.push(e.to);
      } else if (color[e.to] == color[v]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int first_pupil = 0;
    int second_pupil = 0;
    std::cin >> first_pupil >> second_pupil;
    graph[first_pupil].push_back({first_pupil, second_pupil});
    graph[second_pupil].push_back({second_pupil, first_pupil});
  }
  std::vector<std::string> color(n + 1, "white");
  bool is_bipartiteness = true;
  for (int i = 1; i <= n; ++i) {
    if (color[i] == "white") {
      if (!IsBipartitenessnessBFS(graph, i, color)) {
        is_bipartiteness = false;
        break;
      }
    }
  }
  if (is_bipartiteness) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  return 0;
}