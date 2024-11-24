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
    float size = 9.0f;
    float half_size = size / 2.0f;
    cube->vertices = {
        Vector3{-half_size, -half_size, half_size}, // 0: front bottom left
        Vector3{half_size, -half_size, half_size},  // 1: front bottom right
        Vector3{half_size, half_size, half_size},   // 2: front top right
        Vector3{-half_size, half_size, half_size},  // 3: front top left

        // Back face vertices
        Vector3{-half_size, -half_size, -half_size}, // 4: back bottom left
        Vector3{half_size, -half_size, -half_size},  // 5: back bottom right
        Vector3{half_size, half_size, -half_size},   // 6: back top right
        Vector3{-half_size, half_size, -half_size}   // 7: back top left
    };
    cube->faces = {Face{{0, 1, 2}}, Face{{0, 2, 3}}, Face{{1, 5, 6}},
                   Face{{1, 6, 2}}, Face{{5, 4, 7}}, Face{{5, 7, 6}},
                   Face{{4, 0, 3}}, Face{{4, 3, 7}}, Face{{3, 2, 6}},
                   Face{{3, 6, 7}}, Face{{4, 5, 1}}, Face{{4, 1, 0}}};

    auto octahedron = std::make_unique<Mesh>();
    octahedron->vertices = {
        Vector3{0.0f, 5.0f, 0.0f},  // 0: top vertex
        Vector3{5.0f, 0.0f, 0.0f},  // 1: right vertex
        Vector3{0.0f, 0.0f, 5.0f},  // 2: front vertex
        Vector3{-5.0f, 0.0f, 0.0f}, // 3: left vertex
        Vector3{0.0f, 0.0f, -5.0f}, // 4: back vertex
        Vector3{0.0f, -5.0f, 0.0f}  // 5: bottom vertex
    };

    octahedron->faces = {
        Face{{0, 2, 1}}, // top-front-right
        Face{{0, 1, 4}}, // top-right-back
        Face{{0, 4, 3}}, // top-back-left
        Face{{0, 3, 2}}, // top-left-front

        Face{{5, 1, 2}}, // bottom-right-front
        Face{{5, 4, 1}}, // bottom-back-right
        Face{{5, 3, 4}}, // bottom-left-back
        Face{{5, 2, 3}}  // bottom-front-left
    };

    // scene->add(std::move(cube));
    scene->add(std::move(octahedron));
    engine.run();
  } catch (const std::exception &e) {
    std::cerr << "Error " << e.what() << "\n";
  }
  return 0;
}
