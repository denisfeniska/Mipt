#include <iostream>

struct Coordinates {
  int x;
  int y;

  Coordinates() : x(0), y(0) {
  }
};

int main() {
  int x = 0;
  int y = 0;
  int h = 0;
  int w = 0;
  std::cin >> x >> y;
  std::cin >> h >> w;
  int** table = new int*[x];
  for (int i = 0; i < x; ++i) {
    table[i] = new int[y];
    for (int j = 0; j < y; ++j) {
      int room = 0;
      std::cin >> room;
      table[i][j] = room;
    }
  }
  Coordinates curr;
  Coordinates next;
  while (true) {
    next = curr;
    int max_room = table[curr.x][curr.y];
    int stop_x = x <= curr.x + h ? x : curr.x + h;
    int stop_y = y <= curr.y + w ? y : curr.y + w;
    for (int i = curr.x; i < stop_x; ++i) {
      for (int j = curr.y; j < stop_y; ++j) {
        if (table[i][j] > max_room) {
          max_room = table[i][j];
          next.x = i;
          next.y = j;
        }
      }
    }
    if (next.x == curr.x && next.y == curr.y) {
      break;
    }
    curr = next;
  }
  std::cout << curr.x << " " << curr.y << "\n";
  for (int i = 0; i < x; ++i) {
    delete[] table[i];
  }
  delete[] table;
  return 0;
}