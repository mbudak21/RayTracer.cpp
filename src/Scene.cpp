#include "Scene.h"

using namespace std;

Scene::Scene(void) {}

Scene::~Scene() {
    clear();
}

void Scene::addObj(std::shared_ptr<Object> obj) {
    objects.push_back(obj);
}

// void Scene::addSphere(std::shared_ptr<Sphere> sphere) {
//     objects.push_back(sphere);
// }

void Scene::addLight(std::shared_ptr<Light> light) {
    lights.push_back(light);
}

void Scene::clear() {
    // clear objects from memory
    objects.clear();
    lights.clear();
}

int Scene::save(char* fileName) {
    // Save your scene to a file somehow ...
    return 0;
}

void Scene::load(char* fileName) {
    // To avoid memory leaks, we run clear, which deletes any old objects first.
    this->clear();
    // load scene from file here ...
}
