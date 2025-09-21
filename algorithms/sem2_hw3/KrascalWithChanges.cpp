#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int u;
  int v;
  int weight;
  bool operator<(Edge const& o) const {
    return weight < o.weight;
  }
};

void MakeSet(int v, std::vector<int>& root, std::vector<int>& rank, std::vector<int>& sums_cost) {
  root[v] = v;
  rank[v] = 1;
  sums_cost[v] = 1000000;
}

int FindSet(int v, std::vector<int>& root) {
  int parent = root[v];
  while (parent != root[parent]) {
    parent = root[parent];
  }
  while (v != parent) {
    int next = root[v];
    root[v] = parent;
    v = next;
  }
  return parent;
}

int Unite(int a, int b, std::vector<int>& root, std::vector<int>& rank) {
  if (rank[a] < rank[b]) {
    std::swap(a, b);
  }
  root[b] = a;
  if (rank[a] == rank[b]) {
    ++rank[a];
  }
  return a;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Edge> edges;
  edges.reserve(n * (n - 1) / 2 + n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int cost = 0;
      std::cin >> cost;
      if (j > i) {
        edges.push_back({i, j, cost});
      }
    }
  }
  std::vector<int> s_cost(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> s_cost[i];
    edges.push_back({0, i, s_cost[i]});
  }
  std::vector<int> root(n + 1);
  std::vector<int> rank_v(n + 1);
  std::vector<int> mins_cost(n + 1);
  for (int v = 0; v <= n; ++v) {
    MakeSet(v, root, rank_v, mins_cost);
  }
  for (int i = 1; i <= n; ++i) {
    mins_cost[i] = s_cost[i];
  }
  mins_cost[0] = 1000000;
  std::sort(edges.begin(), edges.end());
  int res = 0;
  for (auto& e : edges) {
    int u = e.u;
    int v = e.v;
    int a = FindSet(u, root);
    int b = FindSet(v, root);
    if (a == b) {
      continue;
    }
    int meet_cost = e.weight;
    int send_cost = mins_cost[a] + mins_cost[b];
    if (meet_cost <= send_cost) {
      res += meet_cost;
      int root_unite = Unite(a, b, root, rank_v);
      mins_cost[root_unite] = std::min(mins_cost[a], mins_cost[b]);
    } else {
      res += send_cost;
      int root_unite = Unite(a, b, root, rank_v);
      mins_cost[root_unite] = 1000000;
    }
  }
  std::cout << res << "\n";
  return 0;
}