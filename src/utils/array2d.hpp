#pragma once
#include <cassert>
#include <vector>

#include "utils/rect.hpp"

template <typename T>
class Array2d {
  std::vector<T> _items;

  auto check_bounds(int x, int y) {
    if (x < 0 || x > bounds.width) {
      throw std::out_of_range{
          fmt::format("Position {}.x is out of bounds of {}", Coord{x, y}, bounds)};
    }
    if (y < 0 || y > bounds.height) {
      throw std::out_of_range{
          fmt::format("Position {}.y is out of bounds of {}", Coord{x, y}, bounds)};
    }
  }

  auto calc_index(int x, int y) const -> std::size_t {
    check_bounds(x, y);
    return y * bounds.width + x;
  }

 public:
  const Rect bounds;

  Array2d(int width, int height, const T& init = T{}) : bounds{0, 0, width, height} {
    _items.resize(width * height, init);
  }

  auto operator[](const Coord pos) -> T& { return get(pos.x, pos.y); }
  auto operator[](const Coord pos) -> const T& { return get(pos.x, pos.y); }

  auto get(int x, int y) -> T& { return _items[calc_index(x, y)]; }
  auto get(int x, int y) -> const T& { return _items[calc_index(x, y)]; }

  void fill(const T value) { std::fill(_items.begin(), _items.end(), value); }

  auto begin() { return _items.begin(); }
  auto end() { return _items.end(); }

  auto begin() const { return _items.cbegin(); }
  auto end() const { return _items.cend(); }
};