#pragma once
#include "renderer.hpp"
#include "scene.hpp"

class Engine {
public:
  struct Config {
    struct Renderer::Config renderer_cfg;
    float target_fps{60.0f};
  };

  static constexpr uint32_t FRAME_TARGET_TIME = 1000 / 60;
  explicit Engine(const Config &config);
  Scene *current_scene() const { return this->scene.get(); }
  void run();
  void stop() { running = false; }

private:
  void render();
  void update(float elapsed);
  bool running{false};
  Config config;
  std::unique_ptr<Renderer> renderer;
  std::unique_ptr<Scene> scene;
};
