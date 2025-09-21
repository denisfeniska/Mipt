#include <iostream>
#include <vector>
#include <algorithm>

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
  for (int i = 1; i <= n; ++i) {
    MakeSet(i, root, rank, sum);
  }
  while (m--) {
    int code = 0;
    std::cin >> code;
    if (code == 1) {
      int x = 0;
      int y = 0;
      int weight = 0;
      std::cin >> x >> y >> weight;
      AddEdge(x, y, weight, root, rank, sum);
    } else {
      int x = 0;
      std::cin >> x;
      int root_node = FindSet(x, root);
      std::cout << sum[root_node] << "\n";
    }
  }
  return 0;
}