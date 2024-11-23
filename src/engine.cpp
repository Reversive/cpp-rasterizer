#include "engine.hpp"
#include <stdexcept>

Engine::Engine(const Config &config) : config(config) {
  if (config.target_fps < 0) {
    throw std::invalid_argument("FPS must be greater than 0");
  }

  this->renderer = std::make_unique<Renderer>(config.renderer_cfg);
  this->scene = std::make_unique<Scene>();
}

void Engine::render() {
  this->renderer->set_draw_color(Color(0, 0, 0, 255));
  this->renderer->clear();
  this->scene->draw(*this->renderer);
  this->renderer->present();
}

void Engine::update() { this->scene->update(); }

// TODO: Proper Time Step
void Engine::run() {
  this->running = true;
  while (this->running) {
    // TODO: Make a proper event handler
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
      this->running = false;
      break;
    }
    this->update();
    this->render();
  }
}
