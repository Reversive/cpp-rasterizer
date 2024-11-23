#include "engine.hpp"
#include <stdexcept>

Engine::Engine(const Config &config) : config(config) {
  if (config.target_fps < 0) {
    throw std::invalid_argument("FPS must be greater than 0");
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw std::runtime_error(std::string("SDL Init throwed: ") +
                             SDL_GetError());
  }
  this->initialized = true;
  try {
    this->renderer = std::make_unique<Renderer>(config.renderer_cfg);
    this->scene = std::make_unique<Scene>();
  } catch (const std::exception &e) {
    this->clean_up();
    throw;
  }
}

Engine::~Engine() { this->clean_up(); }

void Engine::clean_up() {
  this->renderer.reset();
  this->scene.reset();
  if (this->initialized) {
    SDL_Quit();
    this->initialized = false;
  }
}

void Engine::render() {
  this->renderer->set_draw_color(Color(0, 0, 0, 255));
  this->renderer->clear();
  this->scene->draw(*this->renderer);
  this->renderer->present();
}

void Engine::update() { this->scene->update(); }

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
