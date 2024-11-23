#pragma once
#include "renderer.hpp"
#include "scene.hpp"

class Engine {
public:
  struct Config {
    struct Renderer::Config renderer_cfg;
    float target_fps{60.0f};
  };

  explicit Engine(const Config &config);
  Scene *current_scene() const { return this->scene.get(); }
  void run();
  void stop() { running = false; }

private:
  void render();
  void update();
  bool running{false};
  Config config;
  std::unique_ptr<Renderer> renderer;
  std::unique_ptr<Scene> scene;
};
