#pragma once
#include <fmt/format.h>

#include <vector>

#include "utils/coord.hpp"

class Rect {
  class Iterator {
    Coord _current_pos;
    const Rect& _parent;

   public:
    Iterator(const Rect& rect) : _parent{rect}, _current_pos{rect.pos()} {}

    auto operator*() const { return _current_pos; }
    auto operator!=(const Coord&) { return _current_pos.y < _parent.bottom(); }
    auto operator++() -> Iterator& {
      _current_pos.x++;
      if (_current_pos.x >= _parent.right()) {
        _current_pos.x = _parent.x;
        _current_pos.y++;
      }
      return *this;
    }
  };

 public:
  int x;
  int y;
  int width;
  int height;

  Rect(int x, int y, int width, int height) : x{x}, y{y}, width{width}, height{height} {}
  Rect(const Coord pos, int width, int height) : x{pos.x}, y{pos.y}, width{width}, height{height} {}

  static Rect from_center(const Coord center, int width, int height) {
    auto x = center.x - (width / 2);
    auto y = center.y - (height / 2);
    return Rect{x, y, width, height};
  }
  static Rect tlbr(const Coord topleft, const Coord bottomright) {
    auto width = bottomright.x - topleft.x;
    auto height = bottomright.y - topleft.y;
    return Rect{topleft.x, topleft.y, width, height};
  }

  auto pos() const -> Coord { return {x, y}; }
  auto size() const -> Coord { return {width, height}; }

  auto left() const -> int { return x; }
  auto right() const -> int { return x + width; }
  auto top() const -> int { return y; }
  auto bottom() const -> int { return y + height; }

  auto topleft() const -> Coord { return {left(), top()}; }
  auto topright() const -> Coord { return {right(), top()}; }
  auto bottomleft() const -> Coord { return {left(), bottom()}; }
  auto bottomright() const -> Coord { return {right(), bottom()}; }

  auto area() const -> int { return width * height; }

  auto begin() const { return Iterator{*this}; }
  auto end() const { return bottomleft(); }

  Rect inflate(int delta) const {
    return Rect{x - delta, y - delta, width + (delta * 2), height + (delta * 2)};
  }

  std::vector<Coord> trace() {
    if ((width > 1) && (height > 1)) {
      auto result = std::vector<Coord>{};

      for (auto x = left(); x < right(); ++x) {
        result.push_back({x, top()});
        result.push_back({x, bottom() - 1});
      }

      for (auto y = top() + 1; y < bottom() - 1; ++y) {
        result.push_back({left(), y});
        result.push_back({right() - 1, y});
      }

      return result;
    }

    return {};
  }
};

template <>
struct fmt::formatter<Rect> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Rect& rect, FormatContext& ctx) {
    return fmt::format_to(
        ctx.out(),
        "[x: {}, y: {}, w: {}, h: {}]",
        rect.x,
        rect.y,
        rect.width,
        rect.height);
  }
};