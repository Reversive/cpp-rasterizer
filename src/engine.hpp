#pragma once
#include "renderer.hpp"

class Engine {
public:
  struct Config {
    struct Renderer::Config renderer_cfg;
    float target_fps{60.0f};
  };
  explicit Engine(const Config &config);
  void run();
  void stop() { running = false; }
  void clean_up();

private:
  bool running{false};
  bool initialized{false};
  std::unique_ptr<Renderer> renderer;
};
