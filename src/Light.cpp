#include "Light.h"
#include <cassert>

Light::Light(Vec3f pos, Vec3f color) : pos(pos) {
        assert(color.x >= 0.0f && color.y >= 0.0f && color.z >= 0.0f); // positive
        assert(color.x <= 1.0f && color.y <= 1.0f && color.z <= 1.0f); // less than 1

        this->color = color;
};

Light::Light(Vec3f pos) : color(Vec3f(1.0f, 1.0f, 1.0f)) { } // white as default
