#include <iostream>

int main() {
  int matr1[3][3];
  int matr2[3][3];
  int matrres[3][3] = {0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cin >> matr1[i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cin >> matr2[i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        matrres[i][j] += matr1[i][k] * matr2[k][j];
      }
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << matrres[i][j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}