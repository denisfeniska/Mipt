#pragma once
#include <vector>
#include <optional>
#include <functional>
#include <random>
#include <algorithm>
#include "universal_hash.h"

template <typename Key, typename BaseHash = std::hash<Key>>
class FrozenSet {

 private:
  struct Bucket {
    std::vector<std::optional<Key>> entries;
    UniversalHash second_hash;
  };

  std::vector<Bucket> buckets_;
  size_t size_ = 0;
  UniversalHash first_hash_;
  BaseHash base_hash_;

  template <typename RandomGenerator>
  void InitializeFirstLevel(RandomGenerator& gen) {
    buckets_.resize(size_);
    first_hash_ = UniversalHash::GenerateHash(gen);
  }

  std::vector<std::vector<Key>> DistributeKeysToBuckets(const std::vector<Key>& keys) {
    std::vector<std::vector<Key>> temp_buckets(size_);
    for (const auto& key : keys) {
      const auto hash_value = first_hash_(base_hash_(key));
      temp_buckets[hash_value % size_].push_back(key);
    }
    return temp_buckets;
  }

  template <typename RandomGenerator>
  void GenerateWithoutCollision(const std::vector<Key>& keys, Bucket& bucket, RandomGenerator& gen) {
    bool flag = true;
    while (flag) {
      flag = false;
      bucket.second_hash = UniversalHash::GenerateHash(gen);
      std::fill(bucket.entries.begin(), bucket.entries.end(), std::nullopt);
      for (const auto& key : keys) {
        const auto position = bucket.second_hash(base_hash_(key)) % bucket.entries.size();
        if (bucket.entries[position].has_value()) {
          flag = true;
          break;
        }
        bucket.entries[position] = key;
      }
    }
  }

  template <typename RandomGenerator>
  void BuildSecondLevelTables(std::vector<std::vector<Key>>& temp_buckets, RandomGenerator& gen) {
    for (size_t i = 0; i < temp_buckets.size(); ++i) {
      auto& bucket_keys = temp_buckets[i];
      if (bucket_keys.empty()) {
        continue;
      }
      buckets_[i].entries.resize(bucket_keys.size() * bucket_keys.size());
      GenerateWithoutCollision(bucket_keys, buckets_[i], gen);
    }
  }

  template <typename Iterator, typename RandomGenerator>
  void Build(Iterator begin, Iterator end, RandomGenerator& gen) {
    std::vector<Key> keys(begin, end);
    size_ = keys.size();
    if (size_ == 0) {
      return;
    }
    InitializeFirstLevel(gen);
    auto temp_buckets = DistributeKeysToBuckets(keys);
    BuildSecondLevelTables(temp_buckets, gen);
  }

 public:
  FrozenSet() : size_(0) {
  }

  template <typename Iterator, typename RandomGenerator>
  FrozenSet(Iterator begin, Iterator end, RandomGenerator& gen) {
    Build(begin, end, gen);
  }

  size_t Size() const {
    return size_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  void Clear() {
    buckets_.clear();
    size_ = 0;
  }

  bool Find(const Key& key) const {
    if (Empty()) {
      return false;
    }
    const auto base_value = base_hash_(key);
    const auto bucket_index = first_hash_(base_value) % buckets_.size();
    const auto& bucket = buckets_[bucket_index];
    if (bucket.entries.empty()) {
      return false;
    }
    const auto position = bucket.second_hash(base_value) % bucket.entries.size();
    return bucket.entries[position].has_value() && bucket.entries[position].value() == key;
  }
};