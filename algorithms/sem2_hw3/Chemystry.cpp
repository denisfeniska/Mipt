#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

struct Edge {
  int to;
  int cap;
  int flow;
  int opposite;
};

class EdmondsKarp {
 public:
  int n_;
  std::vector<std::vector<Edge>> graph_;

  explicit EdmondsKarp(int v) : n_(v) {
    graph_.resize(n_ + 1);
  }

  bool BFS(int s, int ver, std::vector<int>& parent_vect, std::vector<int>& u_index) {
    std::vector<int> dist(graph_.size(), 1e9);
    dist[s] = 0;
    std::fill(parent_vect.begin(), parent_vect.end(), -1);
    parent_vect[s] = s;
    std::queue<int> queue;
    queue.push(s);
    while (!queue.empty() && parent_vect[ver] == -1) {
      int v = queue.front();
      queue.pop();
      for (int i = 0; i < static_cast<int>(graph_[v].size()); ++i) {
        Edge& e = graph_[v][i];
        if (dist[e.to] == 1e9 && e.cap > e.flow) {
          dist[e.to] = dist[v] + 1;
          parent_vect[e.to] = v;
          u_index[e.to] = i;
          queue.push(e.to);
        }
      }
    }
    return parent_vect[ver] != -1;
  }

  int MaxPathFlow(int s, int t) {
    int flow = 0;
    std::vector<int> parent_vect(n_ + 1, -1);
    std::vector<int> u_index(n_ + 1, -1);
    while (BFS(s, t, parent_vect, u_index)) {
      int path_flow = 1e9;
      for (int v = t; v != s; v = parent_vect[v]) {
        int u = parent_vect[v];
        int index = u_index[v];
        if (graph_[u][index].cap - graph_[u][index].flow < path_flow) {
          path_flow = graph_[u][index].cap - graph_[u][index].flow;
        }
      }
      for (int v = t; v != s; v = parent_vect[v]) {
        int u = parent_vect[v];
        int index = u_index[v];
        graph_[u][index].flow += path_flow;
        graph_[v][graph_[u][index].opposite].flow -= path_flow;
      }
      flow += path_flow;
    }
    return flow;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::string> matr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> matr[i];
  }
  std::unordered_map<char, int> v_city;
  v_city['H'] = 1;
  v_city['O'] = 2;
  v_city['N'] = 3;
  v_city['C'] = 4;
  v_city['.'] = 0;
  bool has_element = false;
  int res_v = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (matr[i][j] != '.') {
        has_element = true;
        res_v += v_city[matr[i][j]];
      }
    }
  }
  if (!has_element) {
    std::cout << "Invalid"
              << "\n";
    return 0;
  }
  if (res_v % 2 != 0) {
    std::cout << "Invalid"
              << "\n";
    return 0;
  }
  EdmondsKarp net(n * m + 2);
  int s = 0;
  int t = n * m + 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int v = i * m + j + 1;
      int val = v_city[matr[i][j]];
      if ((i + j) % 2 == 0) {
        net.graph_[s].push_back({v, val, 0, static_cast<int>(net.graph_[v].size())});
        net.graph_[v].push_back({s, 0, 0, static_cast<int>(net.graph_[s].size()) - 1});
        if (j + 1 < m && matr[i][j + 1] != '.') {
          int neighbor = i * m + (j + 1) + 1;
          net.graph_[v].push_back({neighbor, 1, 0, static_cast<int>(net.graph_[neighbor].size())});
          net.graph_[neighbor].push_back({v, 0, 0, static_cast<int>(net.graph_[v].size()) - 1});
        }
        if (i + 1 < n && matr[i + 1][j] != '.') {
          int neighbor = (i + 1) * m + j + 1;
          net.graph_[v].push_back({neighbor, 1, 0, static_cast<int>(net.graph_[neighbor].size())});
          net.graph_[neighbor].push_back({v, 0, 0, static_cast<int>(net.graph_[v].size()) - 1});
        }
        if (j - 1 >= 0 && matr[i][j - 1] != '.') {
          int neighbor = i * m + (j - 1) + 1;
          net.graph_[v].push_back({neighbor, 1, 0, static_cast<int>(net.graph_[neighbor].size())});
          net.graph_[neighbor].push_back({v, 0, 0, static_cast<int>(net.graph_[v].size()) - 1});
        }
        if (i - 1 >= 0 && matr[i - 1][j] != '.') {
          int neighbor = (i - 1) * m + j + 1;
          net.graph_[v].push_back({neighbor, 1, 0, static_cast<int>(net.graph_[neighbor].size())});
          net.graph_[neighbor].push_back({v, 0, 0, static_cast<int>(net.graph_[v].size()) - 1});
        }
      } else {
        net.graph_[v].push_back({t, val, 0, static_cast<int>(net.graph_[t].size())});
        net.graph_[t].push_back({v, 0, 0, static_cast<int>(net.graph_[v].size()) - 1});
      }
    }
  }
  int max_flow = net.MaxPathFlow(s, t);
  if (max_flow == res_v / 2) {
    std::cout << "Valid" << std::endl;
  } else {
    std::cout << "Invalid" << std::endl;
  }
  return 0;
}