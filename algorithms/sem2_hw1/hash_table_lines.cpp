#include <iostream>
#include <unordered_set>
#include <string>
#include <cstdint>

uint64_t MurmurHash64A(const void *key, int len, uint64_t seed) {
  const uint64_t m = 0xc6a4a7935bd1e995ULL;
  const int r = 47;
  uint64_t h = seed ^ (len * m);
  const auto *data = static_cast<const uint64_t *>(key);
  const uint64_t *end = data + (len / 8);
  while (data != end) {
    uint64_t k = *data++;
    k *= m;
    k ^= k >> r;
    k *= m;
    h ^= k;
    h *= m;
  }
  const auto *data2 = reinterpret_cast<const unsigned char *>(data);
  switch (len & 7) {
    case 7:
      h ^= static_cast<uint64_t>(data2[6]) << 48;
    case 6:
      h ^= static_cast<uint64_t>(data2[5]) << 40;
    case 5:
      h ^= static_cast<uint64_t>(data2[4]) << 32;
    case 4:
      h ^= static_cast<uint64_t>(data2[3]) << 24;
    case 3:
      h ^= static_cast<uint64_t>(data2[2]) << 16;
    case 2:
      h ^= static_cast<uint64_t>(data2[1]) << 8;
    case 1:
      h ^= static_cast<uint64_t>(data2[0]);
      h *= m;
  };
  h ^= h >> r;
  h *= m;
  h ^= h >> r;
  return h;
}

struct HashFunc {
  static const uint64_t kSeed = 0x123456789ABCDEF;
  size_t operator()(const std::string &str) const {
    uint64_t elem = MurmurHash64A(str.data(), static_cast<int>(str.size()), kSeed);
    auto sizet_x = static_cast<size_t>(elem);
    return sizet_x;
  }
};

int main() {
  std::unordered_set<std::string, HashFunc> set;
  while (true) {
    std::string str;
    std::getline(std::cin, str);
    if (str[0] == '#') {
      break;
    }
    char operation = str[0];
    std::string line = str.substr(2);
    if (operation == '+') {
      set.insert(line);
    } else if (operation == '-') {
      auto check_line = set.find(line);
      if (check_line != set.end()) {
        set.erase(check_line);
      }
    } else if (operation == '?') {
      auto check_line = set.find(line);
      if (check_line != set.end()) {
        std::cout << "YES"
                  << "\n";
      } else {
        std::cout << "NO"
                  << "\n";
      }
    }
  }
  return 0;
}