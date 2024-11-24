#include "engine.hpp"
#include "mesh.hpp"
#include <exception>
#include <iostream>
#include <memory>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  try {
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
    auto scene = engine.current_scene();
    auto cube = std::make_unique<Mesh>();
    for (float i = -1.f; i <= 1.f; i += 0.25f) {
      for (float j = -1.f; j <= 1.f; j += 0.25f) {
        for (float k = -1.f; k <= 1.f; k += 0.25f) {
          cube->vertices.emplace_back(Vector3{i, j, k});
        }
      }
    }

    scene->add(std::move(cube));
    engine.run();
  } catch (const std::exception &e) {
    std::cerr << "Error " << e.what() << "\n";
  }
  return 0;
}
