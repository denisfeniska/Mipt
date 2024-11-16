#include <iostream>

int** notebook;

bool CheckingSpaces(int* lines, int count, int& space) {
  if (count < 1) {
    return false;
  }
  if (count == 1) {
    space = 0;
    return true;
  }
  space = lines[1] - lines[0];
  if (space < 1) {
    return false;
  }
  for (int i = 2; i < count; ++i) {
    if (lines[i] - lines[i - 1] != space) {
      return false;
    }
  }
  return true;
}

const char* Type(int n, int m) {
  int* horizontal_lines_indexes = new int[n];
  int* vertical_lines_indexes = new int[m];
  int h_count = 0;
  int v_count = 0;
  for (int i = 0; i < n; ++i) {
    bool is_horizontal_line = true;
    for (int j = 0; j < m; ++j) {
      if (notebook[i][j] == 0) {
        is_horizontal_line = false;
        break;
      }
    }
    if (is_horizontal_line) {
      horizontal_lines_indexes[h_count++] = i;
    }
  }
  for (int j = 0; j < m; ++j) {
    bool is_vertical_line = true;
    for (int i = 0; i < n; ++i) {
      if (notebook[i][j] == 0) {
        is_vertical_line = false;
        break;
      }
    }
    if (is_vertical_line) {
      vertical_lines_indexes[v_count++] = j;
    }
  }
  int h_space = 0;
  int v_space = 0;
  bool horizontal = CheckingSpaces(horizontal_lines_indexes, h_count, h_space);
  bool vertical = CheckingSpaces(vertical_lines_indexes, v_count, v_space);
  delete[] horizontal_lines_indexes;
  delete[] vertical_lines_indexes;
  if (horizontal && vertical) {
    return "Square";
  }
  if (!vertical) {
    if (h_count > 1) {
      if (h_space <= m && h_space > 0) {
        return "Line";
      }
      return "?";
    }
    return "?";
  }
  if (!horizontal) {
    if (v_count > 1) {
      if (v_space <= n && v_space > 0) {
        return "Vertical line";
      }
      return "?";
    }
    return "?";
  }
  return "?";
}

int main() {
  int n = 0;
  int m = 0;
  bool has_one = false;
  std::cin >> n >> m;
  notebook = new int*[n];
  for (int i = 0; i < n; ++i) {
    notebook[i] = new int[m];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char ch = '0';
      std::cin >> ch;
      notebook[i][j] = ch - '0';
      if (notebook[i][j] == 1) {
        has_one = true;
      }
    }
  }
  if (n == 1 || m == 1 || !has_one) {
    std::cout << "?\n";
    return 0;
  }
  std::cout << Type(n, m) << "\n";
  for (int i = 0; i < n; ++i) {
    delete[] notebook[i];
  }
  delete[] notebook;
  return 0;
}