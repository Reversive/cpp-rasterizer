#include "engine.hpp"
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  auto config = Engine::Config{
      .renderer_cfg =
          {
              .win_cfg =
                  {
                      .title = "CPP Renderer",
                      .dimensions =
                          {
                              .width = 800,
                              .height = 600,
                              .x = SDL_WINDOWPOS_CENTERED,
                              .y = SDL_WINDOWPOS_CENTERED,
                          },
                      .flags = SDL_WINDOW_BORDERLESS,
                  },
              .fullscreen = false,
          },
  };

  Engine engine{config};
  engine.run();
  return 0;
}
