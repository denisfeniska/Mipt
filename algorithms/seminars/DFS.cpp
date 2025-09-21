#include <iostream>
#include <vector>
#include <stack>

void DFS(int v, std::vector<std::vector<int>> graph, std::vector<std::string> color) {
  color[v] = "grey";
  for (auto& u: graph[v]) {
    if (color[u] == "white") {
      DFS(u, graph, color);
    }
  }
  color[v] = "black";
}

// проверка графа на Эйлеровость
bool IsEuler(std::vector<std::vector<int>> graph) {
  int counter = 0;
  for(int i = 0; i < graph.size(); ++i) {
    if ((graph[i].size()) % 2 == 1) {
      ++counter;
    }
  }
  if (counter > 2) {
    return false;
  }
  std::vector<std::string> color(graph.size(), "white");
  DFS(0, graph, color);
  for (int i = 0; i < graph.size(); ++i) {
    if ((color[i] == "white") && (graph[i].empty())) {
      return false;
    }
  }
  return true;
}

struct edge {
  int to;
  bool is_visited;
};

std::vector<int> Euler(std::vector<std::vector<edge>> graph) {
  int start = 0;
  for (int i = 0; i < graph.size(); ++i) {
    if ((graph[i].size()) % 2 == 1) {
      start = i;
      break;
    }
  }
  std::stack<int> stack;
  std::vector<int> result;
  stack.push(start);
  while (!stack.empty()) {
    int v = stack.top();
    bool visited = false;
    for (auto& u: graph[v]) {
      if (!u.is_visited) {
        stack.push(u.to);
        visited = true;
        u.is_visited = true;
        break;
      }
    }
    if (!visited) {
      result.push_back(v);
      stack.pop();
    }
  }
  return result;
}