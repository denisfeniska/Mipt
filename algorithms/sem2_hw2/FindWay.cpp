#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> BFS(std::vector<std::vector<int>> &city, int n, int m) {
  std::vector<std::vector<int>> res_dist(n, std::vector<int>(m, -1));
  std::queue<std::pair<int, int>> q;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (city[i][j] == 1) {
        res_dist[i][j] = 0;
        q.emplace(i, j);
      }
    }
  }

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    int dx = x - 1;
    int dy = y;
    if (dx >= 0 && dx < n && dy >= 0 && dy < m && res_dist[dx][dy] == -1) {
      res_dist[dx][dy] = res_dist[x][y] + 1;
      q.emplace(dx, dy);
    }

    dx = x + 1;
    dy = y;
    if (dx >= 0 && dx < n && dy >= 0 && dy < m && res_dist[dx][dy] == -1) {
      res_dist[dx][dy] = res_dist[x][y] + 1;
      q.emplace(dx, dy);
    }

    dx = x;
    dy = y - 1;
    if (dx >= 0 && dx < n && dy >= 0 && dy < m && res_dist[dx][dy] == -1) {
      res_dist[dx][dy] = res_dist[x][y] + 1;
      q.emplace(dx, dy);
    }

    dx = x;
    dy = y + 1;
    if (dx >= 0 && dx < n && dy >= 0 && dy < m && res_dist[dx][dy] == -1) {
      res_dist[dx][dy] = res_dist[x][y] + 1;
      q.emplace(dx, dy);
    }
  }

  return res_dist;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<int>> city(n, std::vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x = 0;
      std::cin >> x;
      city[i][j] = x;
    }
  }

  std::vector<std::vector<int>> res_dist = BFS(city, n, m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << res_dist[i][j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}