#pragma once

#include <cmath>
struct Vector2 {
  Vector2(float x, float y) : x(x), y(y) {}
  Vector2 rotate(float angle) {
    return Vector2(x * cosf(angle) - y * sinf(angle),
                   x * sinf(angle) + y * cosf(angle));
  }
  Vector2 translate(float tx, float ty) {
    return Vector2(this->x + tx, this->y + ty);
  }
  Vector2 scale(float sx, float sy) {
    return Vector2(this->x * sx, this->y * sy);
  }

  float x{0.f};
  float y{0.f};
};

struct Vector3 {
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3 rotate_z(float angle) {
    return Vector3(x * cosf(angle) - y * sinf(angle),
                   x * sinf(angle) + y * cosf(angle), z);
  }
  Vector3 rotate_y(float angle) {
    return Vector3(x * cosf(angle) - z * sinf(angle), y,
                   x * sinf(angle) + z * cosf(angle));
  }
  Vector3 rotate_x(float angle) {
    return Vector3(x, y * cosf(angle) - z * sinf(angle),
                   y * sinf(angle) + z * cosf(angle));
  }
  Vector3 translate(float tx, float ty, float tz) {
    return Vector3(this->x + tx, this->y + ty, this->z + tz);
  }
  Vector3 scale(float sx, float sy, float sz) {
    return Vector3(this->x * sx, this->y * sy, this->z * sz);
  }
  float x{0.f};
  float y{0.f};
  float z{0.f};
};
