#include <iostream>
#include <vector>

void MakeSet(int v, std::vector<int>& root, std::vector<int>& rank, std::vector<int>& sum) {
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

void AddEdge(int x, int y, int weight, std::vector<int>& root, std::vector<int>& rank, std::vector<int>& sum) {
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
  std::vector<int> root(n + 1);
  std::vector<int> rank(n + 1);
  std::vector<int> sum(n + 1);
  for (int v = 1; v <= n; ++v) {
    MakeSet(v, root, rank, sum);
  }
  int sum_weight = 0;
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int weight = 0;
    std::cin >> u >> v >> weight;
    int first_v = FindSet(u, root);
    int second_v = FindSet(v, root);
    if (first_v != second_v) {
      sum_weight += weight;
      if (rank[first_v] < rank[second_v]) {
        std::swap(first_v, second_v);
      }
      root[second_v] = first_v;
      if (rank[first_v] == rank[second_v]) {
        rank[first_v]++;
      }
    }
  }
  std::cout << sum_weight << '\n';
  return 0;
}