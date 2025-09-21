#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

bool FindCycle(int v, std::vector<std::vector<int>>& graph, std::vector<std::string>& color, std::vector<int>& path,
               std::vector<int>& cycle) {
  color[v] = "grey";
  path.push_back(v);

  for (int u : graph[v]) {
    if (color[u] == "white") {
      if (FindCycle(u, graph, color, path, cycle)) {
        return true;
      }
    } else if (color[u] == "grey") {
      auto it = find(path.begin(), path.end(), u);
      cycle.assign(it, path.end());
      return true;
    }
  }
  color[v] = "black";
  path.pop_back();
  return false;
}

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<std::vector<int>> graph(n + 1);

  for (int i = 0; i < n - 1; ++i) {
    std::string line;
    std::cin >> line;
    int from = i + 1;
    for (int j = 0; j < n - i - 1; ++j) {
      int to = from + 1 + j;
      if (line[j] == 'R') {
        graph[from].push_back(to);
      } else {
        graph[to].push_back(from);
      }
    }
  }

  std::vector<std::string> color(n + 1, "white");
  std::vector<int> path;
  std::vector<int> cycle;
  bool has_cycle = false;

  for (int v = 1; v < n; ++v) {
    if (color[v] == "white") {
      if (FindCycle(v, graph, color, path, cycle)) {
        has_cycle = true;
        break;
      }
    }
  }
  if (has_cycle) {
    std::cout << "NO"
              << "\n";
  } else {
    std::cout << "YES"
              << "\n";
  }
  return 0;
}