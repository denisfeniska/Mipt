#include <iostream>
#include "cstring.cpp"

int main() {
  // std::cout << Strlen("abcd") << "\n";
  // char a[] = "345";
  // char b[] = "134567";
  // std::cout << Strncmp(a, b, 2);
  // std::cout << Strncmp("abcde", "abcef", 4) << "\n";
  // std::cout << Strncmp("abcde", "abcde", 3) << "\n";
  // std::cout << Strncmp("abcde", "abca", 4) << "\n";
  // std::cout << Strcpy(dest, "abcde") << "\n";
  // char dest[] = "1234567890";
  // std::cout << Strncpy(dest, "000", 12) << "\n";
  // char dest[10] = "abc";
  // std::cout << Strcat(dest, "de") << "\n";
  std::cout << Strspn("abc123abc", "123");
  return 0;
}