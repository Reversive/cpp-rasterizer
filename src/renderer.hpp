#pragma once
#include "window.hpp"
#include <cstdint>

class Renderer {
public:
  struct Config {
    Window::Config win_cfg;
    bool fullscreen{false};
  };
  explicit Renderer(const Config &config);
  void present();
  void set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  void clear();

private:
  struct SDLRendererDeleter {
    void operator()(SDL_Renderer *renderer) {
      if (renderer) {
        SDL_DestroyRenderer(renderer);
      }
    };
  };
  std::unique_ptr<Window> window;
  std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer;
};
