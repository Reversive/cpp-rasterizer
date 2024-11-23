#pragma once

#include "object.hpp"
#include "renderer.hpp"
#include <memory>
#include <vector>

class Scene {
public:
  void add(std::unique_ptr<Object> object);
  void draw(Renderer &renderer);
  void update();

private:
  std::vector<std::unique_ptr<Object>> objects;
};
