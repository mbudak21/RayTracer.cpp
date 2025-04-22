#include "Ray.h"
#include <cmath>
#include <cassert>

float Ray::rayEps = FP_EPSILON;
float Ray::tMax = 1e20f;


// Default constructor: Set the start position of the eye rays to the origin
Ray::Ray() : tClip(tMax), o(Vec3f(0.0f, 0.0f, 0.0f)) {}

Ray::Ray(const Vec3f& o, const Vec3f& d) {
    set_o(o);
    set_d(d);
    this->tClip = tMax;
}

Ray::Ray(const Vec3f& o, const Vec3f& d, float tclip) {
    set_o(o);
    set_d(d);
    this->tClip = tclip;
}

void Ray::epsMoveStartAlongSurfaceNormal(const Vec3f& n) {
    set_o(o + n * rayEps);
}

void Ray::epsMoveStartAlongDir() {
    set_o(o + d * rayEps);
}

void Ray::incRayEps() {
    rayEps *= 10.0f;
}

void Ray::decRayEps() {
    rayEps /= 10.0f;
}

void Ray::set_o(const Vec3f& vec) {
    o = vec;
}

const Vec3f& Ray::get_o() const {
    return o;
}

void Ray::set_d(const Vec3f& vec) {
    // assert(("Ray direction must be normalized", abs(vec.len() - 1.0f) < FP_EPSILON));
    assert((abs(vec.len() - 1.0f) >= FP_EPSILON, "Ray direction must be normalized."));
    this->d = vec;
}

const Vec3f& Ray::get_d() const {
    return this->d;
}