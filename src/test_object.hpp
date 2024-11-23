#pragma once

#include "object.hpp"
class TestObject : public Object {
public:
  void draw(Renderer &renderer) override {
    renderer.draw_pixel(300, 300, 0xFFFF0000);
  }
  void update() override {}

private:
};
