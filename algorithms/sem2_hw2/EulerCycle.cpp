#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>

struct Edge {
  int to;
  bool is_visited;
};

std::vector<int> Euler(std::vector<std::vector<Edge>> &graph) {
  int start = 0;
  for (size_t i = 1; i < graph.size(); ++i) {
    if (!graph[i].empty()) {
      start = static_cast<int>(i);
      break;
    }
  }
  std::vector<size_t> next_edge(graph.size(), 0);
  std::stack<int> stack;
  std::vector<int> result;
  stack.push(start);

  while (!stack.empty()) {
    int v = stack.top();
    while (next_edge[v] < graph[v].size() && graph[v][next_edge[v]].is_visited) {
      ++next_edge[v];
    }
    if (next_edge[v] < graph[v].size()) {
      auto &e = graph[v][next_edge[v]++];
      e.is_visited = true;
      stack.push(e.to);
    } else {
      result.push_back(v);
      stack.pop();
    }
  }
  std::reverse(result.begin(), result.end());
  return result;
}

void DFS(int v, const std::vector<std::vector<int>> &undirected, std::vector<int> &color) {
  color[v] = 1;
  for (int u : undirected[v]) {
    if (color[u] == 0) {
      DFS(u, undirected, color);
    }
  }
}

struct GraphData {
  std::vector<std::vector<Edge>> graph;
  std::vector<int> in_degree;
  std::vector<int> out_degree;
  std::vector<std::vector<int>> undir_graph;
  int total_edges;
};

GraphData ReadInput() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<Edge>> graph(m + 1);
  std::vector<int> in_degree(m + 1, 0);
  std::vector<int> out_degree(m + 1, 0);
  std::vector<std::vector<int>> undir_graph(m + 1);
  int total_edges = 0;

  for (int i = 0; i < n; ++i) {
    int k = 0;
    std::cin >> k;
    std::vector<int> route(k + 1);
    for (int j = 0; j < k + 1; ++j) {
      std::cin >> route[j];
    }
    for (int j = 0; j < k; ++j) {
      int u = route[j];
      int v = route[j + 1];
      graph[u].push_back({v, false});
      out_degree[u]++;
      in_degree[v]++;
      total_edges++;
      undir_graph[u].push_back(v);
      undir_graph[v].push_back(u);
    }
  }

  return {graph, in_degree, out_degree, undir_graph, total_edges};
}

int main() {
  auto data = ReadInput();

  if (data.total_edges == 0) {
    std::cout << 0;
    return 0;
  }

  for (int v = 1; v < static_cast<int>(data.in_degree.size()); ++v) {
    if ((data.in_degree[v] + data.out_degree[v]) > 0 && data.in_degree[v] != data.out_degree[v]) {
      std::cout << 0;
      return 0;
    }
  }

  int start_vertex = 0;
  for (int v = 1; v < static_cast<int>(data.out_degree.size()); ++v) {
    if (data.out_degree[v] > 0) {
      start_vertex = v;
      break;
    }
  }
  if (start_vertex == 0) {
    std::cout << 0;
    return 0;
  }

  std::vector<int> color(data.in_degree.size(), 0);
  DFS(start_vertex, data.undir_graph, color);

  for (int v = 1; v < static_cast<int>(data.in_degree.size()); ++v) {
    if ((data.in_degree[v] + data.out_degree[v]) > 0 && color[v] == 0) {
      std::cout << 0;
      return 0;
    }
  }

  std::vector<int> euler_path = Euler(data.graph);

  if (euler_path.size() != static_cast<size_t>(data.total_edges + 1)) {
    std::cout << 0;
    return 0;
  }

  std::cout << euler_path.size() << "\n";
  for (int v : euler_path) {
    std::cout << v << " ";
  }
  return 0;
}