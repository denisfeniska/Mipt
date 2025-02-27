#include <iostream>
#include <algorithm>

int main() {
  int count = 0;
  std::cin >> count;
  int* arr = new int[count];
  for (int i = 0; i < count; ++i) {
    int elem = 0;
    std::cin >> elem;
    arr[i] = elem;
  }
  int key_value = 0;
  std::cin >> key_value;
  std::cout << std::count(arr, arr + count, key_value);
  delete[] arr;
  return 0;
}