#include "Material.h"
#include <cassert>


Material::Material(Vec3f color){
    assert(color.x >= 0.0f && color.y >= 0.0f && color.z >= 0.0f); // positive
    assert(color.x <= 1.0f && color.y <= 1.0f && color.z <= 1.0f); // less than 1
    this->color = color;
}

Material::Material() : color(Vec3f(1.0f, 0.0f, 0.0f)) { } // Default color is red
void Material::setColor(const Vec3f& vec) {
    this->color = vec;
}
const Vec3f& Material::getColor() const {
    return this->color;
}