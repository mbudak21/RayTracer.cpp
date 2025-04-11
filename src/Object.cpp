#include "Object.h"

// Object::~Object() {};

const Material& Object::getMaterial() const {
    return mat;
}

void Object::setMaterial(const Material& m) {
    mat = m;
}