#include "scene.hpp"

void Scene::add(std::unique_ptr<Object> object) {
  this->objects.push_back(std::move(object));
}
void Scene::draw(Renderer &renderer) {
  for (auto &object : this->objects) {
    object->draw(renderer);
  }
}
void Scene::update() {
  for (auto &object : this->objects) {
    object->update();
  }
}
