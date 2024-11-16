#include <iostream>
#include "sort.h"

int main() {
  int array[5]{3, 5, 1, 4, 2};
  Sort(array + 1, array + 4);
  for (int i = 0; i < 5; ++i) {
    std::cout << array[i] << "\n";
  }
  return 0;
}