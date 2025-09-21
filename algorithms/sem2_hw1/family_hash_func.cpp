#include <iostream>
#include <unordered_set>
#include <string>
#include <cstdint>

struct HashFunc {
  static const int64_t kMod = 1000000007;
  static const int64_t kA = 3539;
  static const int64_t kB = 75757;
  static const int64_t kC = 377337;

  size_t operator()(int number) const {
    int64_t squared = static_cast<int64_t>(number) * number;
    int64_t hash_value = (kA * squared + kB * number + kC) % kMod;
    return static_cast<size_t>(hash_value);
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  std::unordered_set<int, HashFunc> numbers;
  for (int i = 0; i < n; ++i) {
    char operation = '0';
    int number = 0;
    std::cin >> operation >> number;
    if (operation == '+') {
      numbers.insert(number);
    } else if (operation == '-') {
      if (numbers.erase(number)) {
      }
    } else if (operation == '?') {
      std::cout << (numbers.count(number) ? "YES\n" : "NO\n");
    }
  }
  return 0;
}