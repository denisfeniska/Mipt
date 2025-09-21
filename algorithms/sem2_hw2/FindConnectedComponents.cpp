#include <iostream>
#include <vector>
#include <algorithm>

void DFS1(int v, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& order) {
  visited[v] = true;
  for (int u : graph[v]) {
    if (!visited[u]) {
      DFS1(u, graph, visited, order);
    }
  }
  order.push_back(v);
}

std::vector<int> PDFS1(int n, std::vector<std::vector<int>>& graph) {
  std::vector<bool> visited(n + 1, false);
  std::vector<int> order;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      DFS1(i, graph, visited, order);
    }
  }
  reverse(order.begin(), order.end());
  return order;
}

void DFS2(int v, int col, std::vector<std::vector<int>>& r_graph, std::vector<int>& components) {
  components[v] = col;
  for (auto& u : r_graph[v]) {
    if (components[u] == 0) {
      DFS2(u, col, r_graph, components);
    }
  }
}

std::vector<int> PDFS2(std::vector<int>& order, std::vector<std::vector<int>>& r_graph) {
  std::vector<int> components(r_graph.size(), 0);
  int col = 1;
  for (int u : order) {
    if (components[u] == 0) {
      DFS2(u, col, r_graph, components);
      col++;
    }
  }
  return components;
}

std::vector<std::vector<int>> CollectComponents(int n, std::vector<int>& components) {
  int max_col = *max_element(components.begin(), components.end());
  std::vector<std::vector<int>> result(max_col + 1);
  for (int i = 1; i <= n; ++i) {
    result[components[i]].push_back(i);
  }
  return result;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n + 1);
  std::vector<std::vector<int>> h(n + 1);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
    h[v].push_back(u);
    h[u].push_back(v);
  }

  std::vector<int> order = PDFS1(n, g);

  std::vector<int> components = PDFS2(order, h);

  std::vector<std::vector<int>> component_groups = CollectComponents(n, components);

  std::cout << component_groups.size() - 1 << "\n";
  for (size_t i = 1; i < component_groups.size(); ++i) {
    auto& group = component_groups[i];
    std::cout << group.size() << "\n";
    for (size_t j = 0; j < group.size(); ++j) {
      std::cout << group[j] << (j < group.size() - 1 ? " " : "");
    }
    std::cout << "\n";
  }
  return 0;
}