#include "engine.hpp"
#include "time_step.hpp"
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

void Engine::update(float elapsed) { this->scene->update(elapsed); }

void Engine::run() {
  this->running = true;
  TimeStep time_step(60.0);
  while (this->running) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
      this->running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        this->running = false;
      }
      break;
    }
    time_step.update([this](float dt) { this->update(dt); });
    this->render();
  }
}
