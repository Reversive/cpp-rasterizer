#include "renderer.hpp"
#include "vector.hpp"
#include <cmath>
#include <stdexcept>

Renderer::Renderer(const Config &config)
    : window(std::make_unique<Window>(config.win_cfg)) {

  this->width = config.win_cfg.dimensions.width;
  this->height = config.win_cfg.dimensions.height;
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
  this->color_buffer.resize(this->width * this->height, 0xFF000000);
}

SDL_Renderer *Renderer::raw() const { return this->renderer.get(); }

void Renderer::present() {
  SDL_UpdateTexture(this->texture_buffer.get(), nullptr,
                    this->color_buffer.data(), sizeof(uint32_t) * this->width);
  SDL_RenderCopy(this->raw(), this->texture_buffer.get(), nullptr, nullptr);
  SDL_RenderPresent(this->renderer.get());
}

void Renderer::clear() {
  SDL_RenderClear(this->renderer.get());
  this->color_buffer.assign(this->width * this->height, 0xFF000000);
}

void Renderer::set_draw_color(Color color) {
  SDL_SetRenderDrawColor(this->renderer.get(), color.r, color.g, color.b,
                         color.a);
}

void Renderer::draw_pixel(int x, int y, uint32_t color) {
  if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
    return;
  }
  int pixel = (y * this->width) + x;
  this->color_buffer[pixel] = color;
}

void Renderer::draw_rect(int x, int y, int w, int h, uint32_t color) {
  for (int j = y; j < y + h; ++j) {
    for (int i = x; i < x + w; ++i) {
      this->draw_pixel(i, j, color);
    }
  }
}

void Renderer::draw_line(const Vector2 &p0, const Vector2 &p1, uint32_t color) {
  // TODO
  float dx = p1.x - p0.x;
  float dy = p1.y - p0.y;
  float step = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);
  float x_inc = dx / (float)step;
  float y_inc = dy / (float)step;
  float x = p0.x;
  float y = p0.y;
  for (int i = 0; i <= step; i++) {
    this->draw_pixel((int)std::round(x), (int)std::round(y), color);
    x += x_inc;
    y += y_inc;
  }
}

void Renderer::draw_mesh(const Mesh &mesh) {
  for (const auto &face : mesh.faces) {
    Vector3 first = mesh.vertices[face.index.at(0)];
    Vector3 second = mesh.vertices[face.index.at(1)];
    Vector3 third = mesh.vertices[face.index.at(2)];
    first = first.scale(400.f, 400.f, 1.f);
    first = first.translate(0.f, 0.f, -15.f);
    const Vector2 &pr_first = {(first.x / first.z) + (float)this->width / 2,
                               (first.y / first.z) + (float)this->height / 2};
    second = second.scale(400.f, 400.f, 1.f);
    second = second.translate(0.f, 0.f, -15.f);
    const Vector2 &pr_second = {(second.x / second.z) + (float)this->width / 2,
                                (second.y / second.z) +
                                    (float)this->height / 2};
    third = third.scale(400.f, 400.f, 1.f);
    third = third.translate(0.f, 0.f, -15.f);
    const Vector2 &pr_third = {(third.x / third.z) + (float)this->width / 2,
                               (third.y / third.z) + (float)this->height / 2};

    this->draw_line(pr_first, pr_second, 0xFFFFFFFF);
    this->draw_line(pr_second, pr_third, 0xFFFFFFFF);
    this->draw_line(pr_third, pr_first, 0xFFFFFFFF);

    /*world_position = world_position.scale(400.f, 400.f, 1.f);
    world_position = world_position.translate(0.f, 0.f, -15.f);
    Vector2 projected_point{world_position.x / world_position.z,
                            world_position.y / world_position.z};
    this->draw_rect((int)projected_point.x + this->width / 2,
                    (int)projected_point.y + this->height / 2, 2, 2,
                    0xFFFFFFFF);*/
  }
}
