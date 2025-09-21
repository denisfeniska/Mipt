#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<size_t> ComputeFunction(const std::string& str) {
  const size_t length = str.size();
  std::vector<size_t> values(length, 0);
  size_t left = 0;
  size_t right = 0;
  for (size_t current = 1; current < length; ++current) {
    if (current <= right) {
      values[current] = std::min(right - current + 1, values[current - left]);
    }
    while (current + values[current] < length && str[values[current]] == str[current + values[current]]) {
      values[current]++;
    }
    if (current + values[current] - 1 > right) {
      left = current;
      right = current + values[current] - 1;
    }
  }
  return values;
}

std::string CreateCombinedString(const std::string& original) {
  std::string reversed_str(original.rbegin(), original.rend());
  const char separator = '?';
  return original + separator + reversed_str;
}

size_t CalculatePosition(size_t total_length, size_t index) {
  return 2 * total_length + 1 - index;
}

void PrintAValues(const std::vector<size_t>& values, size_t str_length) {
  for (size_t i = 1; i <= str_length; ++i) {
    size_t position = CalculatePosition(str_length, i);
    std::cout << values[position] << ' ';
  }
  std::cout << '\n';
}

int main() {
  size_t str_length = 0;
  std::string input_str;
  std::cin >> str_length >> input_str;
  const std::string combined_str = CreateCombinedString(input_str);
  const std::vector<size_t> values = ComputeFunction(combined_str);
  PrintAValues(values, str_length);
  return 0;
}