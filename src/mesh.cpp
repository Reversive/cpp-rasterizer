#include "mesh.hpp"
#include "renderer.hpp"

void Mesh::draw(Renderer &renderer) { renderer.draw_mesh(*this); }

void Mesh::update(float elapsed) {
  for (auto &vertex : this->vertices) {
    vertex = vertex.rotate_y(elapsed);
  }
}
