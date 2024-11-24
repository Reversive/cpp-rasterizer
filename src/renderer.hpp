#pragma once
#include "color.hpp"
#include "mesh.hpp"
#include "window.hpp"
#include <vector>

class Renderer {
public:
  struct Config {
    Window::Config win_cfg;
    bool fullscreen{false};
  };

  explicit Renderer(const Config &config);
  void clear();
  void present();
  void set_draw_color(Color color);
  void draw_pixel(int x, int y, uint32_t color);
  void draw_mesh(const Mesh &mesh);
  void draw_rect(int x, int y, int w, int h, uint32_t color);
  void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
  SDL_Renderer *raw() const;

private:
  struct SDLRendererDeleter {
    void operator()(SDL_Renderer *renderer) {
      if (renderer) {
        SDL_DestroyRenderer(renderer);
      }
    };
  };
  struct SDLTextureDeleter {
    void operator()(SDL_Texture *texture) {
      if (texture) {
        SDL_DestroyTexture(texture);
      }
    }
  };
  std::vector<uint32_t> color_buffer;
  std::unique_ptr<Window> window;
  std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer;
  std::unique_ptr<SDL_Texture, SDLTextureDeleter> texture_buffer;
  int width, height;
};
