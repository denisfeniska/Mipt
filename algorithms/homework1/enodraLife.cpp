#include <iostream>

int CountNeighbors(int** table, int x, int y, int size) {
  int count = 0;
  if (x - 1 >= 0 && table[x - 1][y] == 1) {
    count += 1;
  }
  if (x + 1 < size && table[x + 1][y] == 1) {
    count += 1;
  }
  if (y - 1 >= 0 && table[x][y - 1] == 1) {
    count += 1;
  }
  if (y + 1 < size && table[x][y + 1] == 1) {
    count += 1;
  }
  if (x - 1 >= 0 && y - 1 >= 0 && table[x - 1][y - 1] == 1) {
    count += 1;
  }
  if (x - 1 >= 0 && y + 1 < size && table[x - 1][y + 1] == 1) {
    count += 1;
  }
  if (x + 1 < size && y - 1 >= 0 && table[x + 1][y - 1] == 1) {
    count += 1;
  }
  if (x + 1 < size && y + 1 < size && table[x + 1][y + 1] == 1) {
    count += 1;
  }
  return count;
}

int main() {
  int size = 0;
  int time = 0;
  std::cin >> size >> time;
  int** table = new int*[size];
  for (int i = 0; i < size; ++i) {
    table[i] = new int[size];
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      char elem = '0';
      std::cin >> elem;
      table[i][j] = elem - '0';
    }
  }
  for (int sec = 0; sec < time; ++sec) {
    int** new_table = new int*[size];
    for (int i = 0; i < size; ++i) {
      new_table[i] = new int[size];
      for (int j = 0; j < size; ++j) {
        new_table[i][j] = table[i][j];
      }
    }
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        int count_neighbors = CountNeighbors(table, i, j, size);
        if (table[i][j] == 1) {
          if (count_neighbors < 2 || count_neighbors > 3) {
            new_table[i][j] = 0;
          }
        } else {
          if (count_neighbors == 3) {
            new_table[i][j] = 1;
          }
        }
      }
    }
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        table[i][j] = new_table[i][j];
      }
      delete[] new_table[i];
    }
    delete[] new_table;
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << table[i][j] << " ";
    }
    std::cout << "\n";
  }
  for (int i = 0; i < size; ++i) {
    delete[] table[i];
  }
  delete[] table;
  return 0;
}