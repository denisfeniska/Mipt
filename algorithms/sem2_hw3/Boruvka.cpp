#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

struct Edge {
  int u;
  int v;
  int64_t w;
};

void MakeSet(int v, std::vector<int>& root, std::vector<int>& rank, std::vector<int64_t>& sum) {
  root[v] = v;
  rank[v] = 1;
  sum[v] = 0;
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

void AddEdge(int x, int y, int64_t weight, std::vector<int>& root, std::vector<int>& rank, std::vector<int64_t>& sum) {
  int a = FindSet(x, root);
  int b = FindSet(y, root);
  if (a == b) {
    sum[a] += weight;
  } else {
    if (rank[a] < rank[b]) {
      std::swap(a, b);
    }
    root[b] = a;
    sum[a] += sum[b] + weight;
    if (rank[a] == rank[b]) {
      rank[a]++;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<Edge> edges(m);
  for (int i = 0; i < m; i++) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    edges[i] = {u - 1, v - 1, w};
  }
  std::vector<int> root(n);
  std::vector<int> rank(n);
  std::vector<int64_t> sum(n);
  for (int i = 0; i < n; i++) {
    MakeSet(i, root, rank, sum);
  }
  int components_count = n;
  std::vector<int> cheapest(n, -1);
  while (components_count > 1) {
    std::fill(cheapest.begin(), cheapest.end(), -1);
    for (int i = 0; i < m; i++) {
      auto& e = edges[i];
      int first = FindSet(e.u, root);
      int second = FindSet(e.v, root);
      if (first == second) {
        continue;
      }
      if (cheapest[first] == -1 || edges[cheapest[first]].w > e.w) {
        cheapest[first] = i;
      }
      if (cheapest[second] == -1 || edges[cheapest[second]].w > e.w) {
        cheapest[second] = i;
      }
    }

    for (int comp = 0; comp < n && components_count > 1; comp++) {
      int idx = cheapest[comp];
      if (idx == -1) {
        continue;
      }
      auto& e = edges[idx];
      int first = FindSet(e.u, root);
      int second = FindSet(e.v, root);
      if (first != second) {
        AddEdge(e.u, e.v, e.w, root, rank, sum);
        components_count--;
      }
    }
  }
  int64_t res_weight = sum[FindSet(0, root)];
  std::cout << res_weight << "\n";
  return 0;
}