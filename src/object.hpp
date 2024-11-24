#pragma once

class Renderer;

class Object {
public:
  virtual void draw(Renderer &renderer) = 0;
  virtual void update(float elapsed) = 0;
  virtual ~Object() = default;
};
