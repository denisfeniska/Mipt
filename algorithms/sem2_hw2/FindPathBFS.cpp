#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

struct Move {
  std::string from;
  std::string to;
};

std::vector<Move> GenerateNeighbors(const std::string &combo) {
  std::vector<Move> neighbors;
  if (combo[0] != '9') {
    std::string next = combo;
    next[0] = static_cast<char>(combo[0] + 1);
    neighbors.push_back({combo, next});
  }

  if (combo[3] != '1') {
    std::string next = combo;
    next[3] = static_cast<char>(combo[3] - 1);
    neighbors.push_back({combo, next});
  }

  std::string rotate_right = combo.substr(3, 1) + combo.substr(0, 3);
  neighbors.push_back({combo, rotate_right});

  std::string rotate_left = combo.substr(1, 3) + combo.substr(0, 1);
  neighbors.push_back({combo, rotate_left});
  return neighbors;
}

std::vector<std::string> FindShortestPath(std::string &start, std::string &goal) {
  std::unordered_map<std::string, std::string> predecessor;
  std::unordered_map<std::string, int> distance;
  std::queue<std::string> q;

  distance[start] = 0;
  predecessor[start] = "";
  q.push(start);

  while (!q.empty()) {
    std::string current = q.front();
    q.pop();

    if (current == goal) {
      break;
    };

    for (auto &move : GenerateNeighbors(current)) {
      std::string &nbr = move.to;
      if (!distance.count(nbr)) {
        distance[nbr] = distance[current] + 1;
        predecessor[nbr] = current;
        q.push(nbr);
      }
    }
  }

  std::vector<std::string> path;
  if (!predecessor.count(goal)) {
    return path;
  }

  for (std::string at = goal; !at.empty(); at = predecessor[at]) {
    path.push_back(at);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

int main() {
  std::string start_combo;
  std::string end_combo;
  std::cin >> start_combo >> end_combo;

  auto path = FindShortestPath(start_combo, end_combo);

  if (path.empty()) {
    std::cout << "0"
              << "\n";
  } else {
    std::cout << path.size() << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
      if (i > 0) {
        std::cout << " ";
      }
      std::cout << path[i];
    }
    std::cout << "\n";
  }
  return 0;
}