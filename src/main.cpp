#include "engine.hpp"
#include "test_object.hpp"
#include <exception>
#include <iostream>

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
    scene->add(std::make_unique<TestObject>());
    engine.run();
  } catch (const std::exception &e) {
    std::cerr << "Error " << e.what() << "\n";
  }
  return 0;
}
