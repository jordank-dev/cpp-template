#pragma once
#include <iterator>
#include <random>
#include <vector>

class Rng {
  std::mt19937 _urng;

  using RandInt = std::uniform_int_distribution<>;
  using RandFloat = std::uniform_real_distribution<double>;

  template <typename Iterator>
  Iterator select(Iterator begin, Iterator end) {
    std::advance(begin, range(std::distance(begin, end)));
    return begin;
  }

 public:
  Rng(int seed) : _urng{seed} {}

  void set_seed(int seed) { _urng.seed(seed); }

  auto range(int min, int max = 0) -> int {
    if (max == 0) {
      return RandInt{0, max - 1}(_urng);
    }
    return RandInt{min, max - 1}(_urng);
  }
  auto inclusive_range(int min, int max = 0) -> int {
    if (max == 0) {
      return RandInt{0, max}(_urng);
    }
    return RandInt{min, max}(_urng);
  }

  auto one_in(int n) -> bool { return range(n) == 0; }

  template <typename Container>
  auto item_in(const Container& items) -> decltype(*std::begin(items))& {
    return *select(std::begin(items), std::end(items));
  }

  template <typename Container>
  auto shuffle(Container& c) {
    std::shuffle(std::begin(c), std::end(c), _urng);
  }
};