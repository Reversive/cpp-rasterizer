#pragma once
#include "renderer.hpp"

class Object {
public:
  virtual void draw(Renderer &renderer) = 0;
  virtual void update() = 0;
  virtual ~Object() = default;
};
