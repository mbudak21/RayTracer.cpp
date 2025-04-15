#include "Material.h"
#include <cassert>

Material::Material() 
: color(Vec3f(1.0f, 0.0f, 0.0f)), // default: red
  shininess(1.0f),
  specularColor(Vec3f(1.0f, 1.0f, 1.0f)),
  ref(0.0f)
{}

Material::Material(Vec3f color) {
  assert(color.x >= 0.0f && color.y >= 0.0f && color.z >= 0.0f); // positive
  assert(color.x <= 1.0f && color.y <= 1.0f && color.z <= 1.0f); // less than 1
  this->color = color;
}

Material::Material(Vec3f color, float shininess, Vec3f specularColor, float ref){
    assert(color.x >= 0.0f && color.y >= 0.0f && color.z >= 0.0f); // positive
    assert(color.x <= 1.0f && color.y <= 1.0f && color.z <= 1.0f); // less than 1
    this->color = color;
    this->shininess = shininess;
    this->specularColor = specularColor;
    this->ref = ref;
}

// Material::Material() : color(Vec3f(1.0f, 0.0f, 0.0f)) { } // Default color is red
// void Material::setColor(const Vec3f& vec) {
//     this->color = vec;
// }
const Vec3f& Material::getColor() const {
    return this->color;
}