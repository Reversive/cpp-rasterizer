#pragma once

#include <cstdint>
struct Color {
  uint8_t r{0}, g{0}, b{0}, a{255};
  constexpr Color() = default;
  constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
      : r(r), g(g), b(b), a(a) {}
};
