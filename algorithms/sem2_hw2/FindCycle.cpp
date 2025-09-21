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
  int m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n + 1);
  std::vector<std::string> color(n + 1, "white");
  std::vector<int> path;
  std::vector<int> cycle;

  for (int i = 0; i < m; ++i) {
    int first = 0;
    int second = 0;
    std::cin >> first >> second;
    graph[first].push_back(second);
  }

  for (int v = 0; v < n; ++v) {
    if (color[v] == "white") {
      if (FindCycle(v, graph, color, path, cycle)) {
        std::cout << "YES"
                  << "\n";
        for (int elem : cycle) {
          std::cout << elem << " ";
        }
        return 0;
      }
    }
  }

  std::cout << "NO"
            << "\n";
  return 0;
}