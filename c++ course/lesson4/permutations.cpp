#include <iostream>
#include <cstring>

void Permutations(char* str, int left, int right) {
  if (left == right) {
    std::cout << str << "\n";
  } else {
    for (int i = left; i <= right; i++) {
      std::swap(str[left], str[i]);
      Permutations(str, left + 1, right);
      std::swap(str[left], str[i]);
    }
  }
}

int MyStrlen(const char* str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

int main() {
  char str[100];
  std::cin >> str;
  int size = MyStrlen(str);
  Permutations(str, 0, size - 1);
  return 0;
}