#pragma once
#include <cstdint>
#include <random>

class UniversalHash {

 private:
  uint64_t multiplier_;
  uint64_t shift_;

  static uint64_t ValidateMultiplier(uint64_t multiplier) {
    if (multiplier == 0 || multiplier >= kPrimeModul) {
      return 1;
    }
    return multiplier;
  }

  uint64_t HashFormula(uint64_t key) const {
    return (multiplier_ * key + shift_) % kPrimeModul;
  }

  template <typename RandomGenerator>
  static uint64_t GenerateRandomMultiplier(RandomGenerator& generator) {
    std::uniform_int_distribution<uint64_t> dist(1, kPrimeModul - 1);
    return dist(generator);
  }

  template <typename RandomGenerator>
  static uint64_t GenerateRandomShift(RandomGenerator& generator) {
    std::uniform_int_distribution<uint64_t> dist(0, kPrimeModul - 1);
    return dist(generator);
  }

 public:
  static const uint64_t kPrimeModul = 1000000007;
  static const uint64_t kMaxValue = kPrimeModul - 1;

  explicit UniversalHash(uint64_t multiplier = 1, uint64_t shift = 0)
      : multiplier_(ValidateMultiplier(multiplier)), shift_(shift % kPrimeModul) {
  }

  uint64_t operator()(uint64_t key) const {
    return HashFormula(key);
  }

  template <typename RandomGenerator>
  static UniversalHash GenerateHash(RandomGenerator& generator) {
    return UniversalHash(GenerateRandomMultiplier(generator), GenerateRandomShift(generator));
  }
};