#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

struct PairHash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    return hash1 ^ (hash2 << 1);
  }
};

bool InitFirstCheck(int m, const std::string& atoms, std::vector<int>& connections,
                    std::vector<std::vector<int>>& graph) {
  std::unordered_set<std::pair<int, int>, PairHash> used;
  for (int i = 0; i < m; ++i) {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;
    --a;
    --b;
    if (a == b) {
      return false;
    }
    int first = std::min(a, b);
    int second = std::max(a, b);
    auto p = std::make_pair(first, second);
    if (used.count(p)) {
      return false;
    }
    used.insert(p);
    if (atoms[a] == 'H' && atoms[b] == 'H') {
      return false;
    }
    if ((atoms[a] == 'C' && connections[a] + 1 > 4) || (atoms[a] == 'H' && connections[a] + 1 > 1) ||
        (atoms[b] == 'C' && connections[b] + 1 > 4) || (atoms[b] == 'H' && connections[b] + 1 > 1)) {
      return false;
    }
    connections[a]++;
    connections[b]++;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  return true;
}

bool CheckDegrees(const std::string& atoms, const std::vector<int>& conn) {
  for (size_t i = 0; i < atoms.size(); ++i) {
    if (atoms[i] == 'C' && conn[i] != 4) {
      return false;
    }
    if (atoms[i] == 'H' && conn[i] != 1) {
      return false;
    }
  }
  return true;
}

bool IsConnected(const std::vector<std::vector<int>>& graph) {
  int n = static_cast<int>(graph.size());
  if (n == 0) {
    return true;
  }
  std::vector<bool> visited(n, false);
  std::vector<int> q;
  q.reserve(n);
  q.push_back(0);
  visited[0] = true;
  int seen = 1;
  for (size_t i = 0; i < q.size(); ++i) {
    int v = q[i];
    for (int u : graph[v]) {
      if (!visited[u]) {
        visited[u] = true;
        ++seen;
        q.push_back(u);
      }
    }
  }
  return seen == n;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::string atoms;
  std::cin >> atoms;

  if (m != n - 1) {
    std::cout << "NO\n";
    return 0;
  }

  std::vector<int> conn(n, 0);
  std::vector<std::vector<int>> graph(n);

  for (int i = 0; i < n; ++i) {
    if (atoms[i] == 'C') {
      graph[i].reserve(4);
    } else {
      graph[i].reserve(1);
    }
  }

  if (!InitFirstCheck(m, atoms, conn, graph)) {
    std::cout << "NO\n";
    return 0;
  }

  if (!CheckDegrees(atoms, conn)) {
    std::cout << "NO\n";
    return 0;
  }

  if (!IsConnected(graph)) {
    std::cout << "NO\n";
    return 0;
  }

  std::cout << "YES\n";
  return 0;
}