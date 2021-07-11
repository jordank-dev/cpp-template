#pragma once
#include <array>

#include "utils/coord.hpp"

struct Direction {
  const int x;
  const int y;
};

inline auto operator+=(const Coord& pos, const Direction dir) -> Coord {
  auto result = pos;
  result.x += dir.x;
  result.y += dir.y;
  return result;
}

inline auto operator-=(const Coord& pos, const Direction dir) -> Coord {
  auto result = pos;
  result.x -= dir.x;
  result.y -= dir.y;
  return result;
}

inline auto operator*(const Direction dir, int scale) -> Direction {
  return {dir.x * scale, dir.y * scale};
}

namespace directions {
static const auto none = Direction{0, 0};
static const auto n = Direction{0, -1};
static const auto s = Direction{0, 1};
static const auto e = Direction{1, 0};
static const auto w = Direction{-1, 0};
static const auto ne = Direction{1, -1};
static const auto nw = Direction{-1, -1};
static const auto se = Direction{1, 1};
static const auto sw = Direction{-1, 1};

static const Direction all[] = {n, ne, e, se, s, sw, w, nw};
static const Direction cardinal[] = {n, e, s, w};
static const Direction intercardinal[] = {ne, se, sw, nw};
};  // namespace directions