#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

const int kPrimaryConst = 911382629;
const int kSecondaryConst = 1000000007;

std::vector<int64_t> ComputePowers(size_t length) {
  std::vector<int64_t> results(length + 1);
  results[0] = 1;
  for (size_t i = 1; i <= length; ++i) {
    results[i] = (results[i - 1] * kPrimaryConst) % kSecondaryConst;
  }
  return results;
}

std::vector<int64_t> ComputePrefixHashes(const std::string &text) {
  size_t text_length = text.size();
  std::vector<int64_t> hashes(text_length + 1);
  for (size_t i = 0; i < text_length; ++i) {
    hashes[i + 1] = (hashes[i] * kPrimaryConst + text[i]) % kSecondaryConst;
  }
  return hashes;
}

int64_t ComputeSubhash(const std::vector<int64_t> &ph, const std::vector<int64_t> &pw, size_t start, size_t end) {
  size_t len = end - start;
  int64_t result = (ph[end] - ph[start] * pw[len]) % kSecondaryConst;
  return result < 0 ? result + kSecondaryConst : result;
}

void ProcessAllSubstrings(const std::string &text, std::unordered_set<int64_t> &storage) {
  size_t total_len = text.size();
  auto power_values = ComputePowers(total_len);
  auto hash_values = ComputePrefixHashes(text);
  for (size_t substr_len = 1; substr_len <= total_len; ++substr_len) {
    size_t max_start = total_len - substr_len;
    for (size_t start_pos = 0; start_pos <= max_start; ++start_pos) {
      size_t end_pos = start_pos + substr_len;
      int64_t current_hash = ComputeSubhash(hash_values, power_values, start_pos, end_pos);
      storage.insert(current_hash);
    }
  }
}

int main() {
  std::string input_data;
  std::cin >> input_data;
  if (input_data.empty()) {
    std::cout << 0 << "\n";
    return 0;
  }
  std::unordered_set<int64_t> hash_storage;
  ProcessAllSubstrings(input_data, hash_storage);
  std::cout << hash_storage.size() << "\n";
  return 0;
}