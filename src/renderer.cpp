#include "renderer.hpp"
#include <stdexcept>

Renderer::Renderer(const Config &config)
    : window(std::make_unique<Window>(config.win_cfg)) {

  SDL_Renderer *raw_renderer =
      SDL_CreateRenderer(window->get_sdl_window(), -1, 0);

  if (raw_renderer == nullptr) {
    throw std::runtime_error(std::string("SDL_CreateRenderer threw ") +
                             SDL_GetError());
  }

  this->renderer.reset(raw_renderer);
}

void Renderer::present() { SDL_RenderPresent(this->renderer.get()); }

void Renderer::clear() { SDL_RenderClear(this->renderer.get()); }

void Renderer::set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(this->renderer.get(), r, g, b, a);
}
