#include "renderer.hpp"
#include <stdexcept>

Renderer::Renderer(const Config &config)
    : window(std::make_unique<Window>(config.win_cfg)) {

  this->pitch = config.win_cfg.dimensions.width;
  SDL_Renderer *raw_renderer =
      SDL_CreateRenderer(window->current_window(), -1, 0);

  if (raw_renderer == nullptr) {
    throw std::runtime_error(std::string("SDL_CreateRenderer returned ") +
                             SDL_GetError());
  }
  this->renderer.reset(raw_renderer);

  SDL_Texture *raw_texture = SDL_CreateTexture(
      this->raw(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
      config.win_cfg.dimensions.width, config.win_cfg.dimensions.height);

  if (raw_texture == nullptr) {
    throw std::runtime_error(std::string(
        std::string("SDL_CreateTexture returned ") + SDL_GetError()));
  }

  this->texture_buffer.reset(raw_texture);
  this->color_buffer.resize(config.win_cfg.dimensions.width *
                                config.win_cfg.dimensions.height,
                            0xFF000000);
}

SDL_Renderer *Renderer::raw() const { return this->renderer.get(); }

void Renderer::present() {
  SDL_UpdateTexture(this->texture_buffer.get(), nullptr,
                    this->color_buffer.data(), sizeof(uint32_t) * this->pitch);
  SDL_RenderCopy(this->raw(), this->texture_buffer.get(), nullptr, nullptr);
  SDL_RenderPresent(this->renderer.get());
}

void Renderer::clear() { SDL_RenderClear(this->renderer.get()); }

void Renderer::set_draw_color(Color color) {
  SDL_SetRenderDrawColor(this->renderer.get(), color.r, color.g, color.b,
                         color.a);
}

void Renderer::draw_pixel(int x, int y, uint32_t color) {
  int pixel = y * this->pitch + x;
  this->color_buffer[pixel] = color;
}
