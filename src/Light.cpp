#include "Light.h"
#include <cassert>

// Vec3f ambC; // ambient color
// Vec3f diffC; // diffuse color
// Vec3f specC; // specular color

Light::Light(Vec3f pos, Color color) : pos(pos), color(color) {};


const Vec3f& Light::getAmbient() const {
    return this->color.ambient;
  }
  const Vec3f& Light::getDiffuse() const {
    return this->color.diffuse;
  }
  const Vec3f& Light::getSpecular() const {
    return this->color.specular;
  }