#include <fmt/format.h>
#include <fmt/ranges.h>

#include "utils/rect.hpp"
#include "utils/rng.hpp"

int main() {
  auto rng = Rng{10172000};

  auto items = std::vector{1, 2, 3, 4, 5, 6, 7};
  fmt::print("Before: {}\n", items);
  rng.shuffle(items);
  fmt::print("After: {}\n", items);
}