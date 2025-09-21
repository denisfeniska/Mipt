#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int from;
  int to;
};

std::vector<int> BFS(const std::vector<std::vector<Edge>>& graph, int s, std::vector<bool>& visited) {
  std::vector<int> city;
  if (visited[s]) {
    return city;
  }
  std::queue<int> queue;
  queue.push(s);
  visited[s] = true;
  city.push_back(s);
  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    for (auto& e : graph[v]) {
      if (!visited[e.to]) {
        visited[e.to] = true;
        queue.push(e.to);
        city.push_back(e.to);
      }
    }
  }
  return city;
}

bool ClosestNeighbor(int x, int y, const std::vector<std::vector<int>>& height_matrix) {
  int dx[] = {-1, 0, 1, 0};
  int dy[] = {0, -1, 0, 1};
  int curr_height = height_matrix[x][y];
  size_t n = height_matrix.size();
  size_t m = height_matrix[0].size();
  for (int i = 0; i < 4; ++i) {
    int neighbor_h = 0;
    if (x + dx[i] < 0 || x + dx[i] >= static_cast<int>(n) || y + dy[i] < 0 || y + dy[i] >= static_cast<int>(m)) {
      neighbor_h = 10001;
    } else {
      neighbor_h = height_matrix[x + dx[i]][y + dy[i]];
    }
    if (neighbor_h < curr_height) {
      return true;
    }
  }
  return false;
}

bool IsVodos(const std::vector<int>& city, const std::vector<std::vector<int>>& height_matrix) {
  size_t m = height_matrix[0].size();
  for (int v : city) {
    if (ClosestNeighbor(v / static_cast<int>(m), v % static_cast<int>(m), height_matrix)) {
      return false;
    }
  }
  return true;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> height_matrix(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> height_matrix[i][j];
    }
  }

  std::vector<std::vector<Edge>> graph(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int v = i * m + j;
      int h = height_matrix[i][j];
      int dx[] = {-1, 1, 0, 0};
      int dy[] = {0, 0, -1, 1};
      for (int k = 0; k < 4; ++k) {
        if (i + dx[k] >= 0 && i + dx[k] < n && j + dy[k] >= 0 && j + dy[k] < m) {
          if (height_matrix[i + dx[k]][j + dy[k]] == h) {
            int u = (i + dx[k]) * m + (j + dy[k]);
            graph[v].push_back({v, u});
          }
        }
      }
    }
  }
  std::vector<bool> visited(n * m, false);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int v = i * m + j;
      if (!visited[v]) {
        std::vector<int> city = BFS(graph, v, visited);
        if (IsVodos(city, height_matrix)) {
          count++;
        }
      }
    }
  }
  std::cout << count << "\n";
  return 0;
}