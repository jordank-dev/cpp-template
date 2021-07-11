#pragma once
#include <fmt/format.h>

#include <compare>

struct Coord {
  int x{0};
  int y{0};

  auto operator<=>(const Coord&) const = default;
};

template <>
struct fmt::formatter<Coord> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Coord& coord, FormatContext& ctx) {
    return fmt::format_to(ctx.out(), "[x: {}, y: {}]", coord.x, coord.y);
  }
};