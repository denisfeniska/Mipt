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
  std::vector<int> key_place(n + 1);
  std::vector<std::vector<int>> graph(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> key_place[i];
    graph[key_place[i]].push_back(i);
  }

  std::vector<std::string> color(n + 1, "white");

  int count_cycles = 0;
  std::vector<int> path;
  std::vector<int> cycle;

  for (int i = 1; i <= n; i++) {
    if (color[i] == "white") {
      path.clear();
      cycle.clear();
      if (FindCycle(i, graph, color, path, cycle)) {
        count_cycles++;
      }
    }
  }
  std::cout << count_cycles << "\n";
  return 0;
}