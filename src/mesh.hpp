#pragma once

#include "object.hpp"
#include "vector.hpp"
#include <array>
#include <vector>

struct Face {
  std::array<uint32_t, 3> index;
};

class Mesh : public Object {
public:
  std::vector<Vector3> vertices;
  std::vector<Face> faces;
  Vector3 rotation{0.f, 0.f, 0.f};
  void draw(Renderer &renderer) override;
  void update(float elapsed) override;
};
