#include <iostream>
#include <vector>
#include <deque>
#include <utility>

std::vector<int> ZeroOneBFS(int s, int n, std::vector<std::vector<std::pair<int, int>>>& city,
                            std::vector<bool>& targets, int targets_rem) {
  std::vector<int> res_dist(n + 1, 1e9);
  std::deque<int> q;

  res_dist[s] = 0;
  q.push_back(s);

  while (!q.empty() && targets_rem > 0) {
    int v = q.front();
    q.pop_front();

    if (targets[v]) {
      targets[v] = false;
      targets_rem--;
      if (targets_rem == 0) {
        break;
      }
    }

    for (auto& [u, weight] : city[v]) {
      if (res_dist[u] > res_dist[v] + weight) {
        res_dist[u] = res_dist[v] + weight;
        if (weight == 0) {
          q.push_front(u);
        } else {
          q.push_back(u);
        }
      }
    }
  }
  return res_dist;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> city(n + 1);

  for (int i = 0; i < m; ++i) {
    int first_sq = 0;
    int second_sq = 0;
    std::cin >> first_sq >> second_sq;
    city[first_sq].emplace_back(second_sq, 0);
    city[second_sq].emplace_back(first_sq, 1);
  }

  int k = 0;
  std::cin >> k;

  std::vector<std::vector<std::pair<int, int>>> by_source(n + 1);
  std::vector<int> answer(k, -1);

  for (int i = 0; i < k; ++i) {
    int first_sq = 0;
    int second_sq = 0;
    std::cin >> first_sq >> second_sq;
    by_source[first_sq].emplace_back(second_sq, i);
  }

  for (int s = 1; s <= n; ++s) {
    if (by_source[s].empty()) {
      continue;
    }

    std::vector<bool> targets(n + 1, false);
    int cnt = 0;
    for (auto& p : by_source[s]) {
      int target = p.first;
      if (!targets[target]) {
        targets[target] = true;
        cnt++;
      }
    }

    std::vector<int> res_dist = ZeroOneBFS(s, n, city, targets, cnt);

    for (auto& p : by_source[s]) {
      int target = p.first;
      int idx = p.second;
      answer[idx] = (res_dist[target] == 1e9 ? -1 : res_dist[target]);
    }
  }

  for (int i = 0; i < k; i++) {
    std::cout << answer[i] << "\n";
  }
  return 0;
}
