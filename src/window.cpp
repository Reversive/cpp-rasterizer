#include "window.hpp"
#include <stdexcept>

Window::Window(const Config &config) : config(config) {
  if (config.dimensions.width <= 0 || config.dimensions.height <= 0) {
    throw std::invalid_argument("Window dimensions must be positive");
  }

  SDL_Window *raw_window = SDL_CreateWindow(
      config.title.c_str(), config.dimensions.x, config.dimensions.y,
      config.dimensions.width, config.dimensions.height, config.flags);

  if (raw_window == nullptr) {
    throw std::runtime_error(std::string("SDL_CreateWindow returned: ") +
                             SDL_GetError());
  }

  this->window.reset(raw_window);
}

SDL_Window *Window::current_window() const { return this->window.get(); }
