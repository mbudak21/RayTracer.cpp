#include "Material.h"
#include <vector>


Material::Material()
  :color(Color(
    Vec3f(0.2f, 0.2f, 0.2f),  // ambient
    Vec3f(0.5f, 0.5f, 0.5f),  // diffuse
    Vec3f(0.3f, 0.3f, 0.3f)   // specular
  )),
  shininess(16.0f),
  ref(0.0f),
  fuzz(0.0f),
  refrIndex(1.0f)
{};

Material::Material(const Color& color, float shininess, float ref): 
  color(color), 
  shininess(shininess), 
  ref(ref), 
  fuzz(0.0f), 
  trnsp(0.0f),
  refrIndex(1.0f) {};

Material::Material(const Color& color, float shininess): color(color), fuzz(0.0f), trnsp(0.0f), refrIndex(1.0f) {
  this->shininess = shininess*128; // Multiplying by 128 as per the reference
  this->ref = (color.specular.x + color.specular.y + color.specular.z) * 2 / (this->shininess);
}

const Vec3f& Material::getAmbient() const {
  return this->color.ambient;
}
const Vec3f& Material::getDiffuse() const {
  return this->color.diffuse;
}
const Vec3f& Material::getSpecular() const {
  return this->color.specular;
}
const float Material::getShine() const {
  return this->shininess;
}
const float Material::getRef() const {
  return this->ref;
}
const float Material::getFuzz() const {
  return this->fuzz;
}
const float Material::getTrnsp() const {
  return this->trnsp;
}
const float Material::getRefrIndex() const {
  return this->refrIndex;
}