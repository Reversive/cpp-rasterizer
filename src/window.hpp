#pragma once
#include <SDL.h>
#include <cstdint>
#include <memory>
#include <string>

class Window {
public:
  struct Dimensions {
    int width{0}, height{0};
    int x{0}, y{0};
  };

  struct Config {
    std::string title;
    struct Dimensions dimensions;
    uint32_t flags{0};
  };

  explicit Window(const Config &config);
  SDL_Window *get_sdl_window() const;

private:
  struct SDLWindowDeleter {
    void operator()(SDL_Window *window) {
      if (window) {
        SDL_DestroyWindow(window);
      }
    }
  };
  std::unique_ptr<SDL_Window, SDLWindowDeleter> window;
  Config config;
};
