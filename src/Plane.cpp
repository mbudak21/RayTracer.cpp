#include "Plane.h"

Plane::~Plane() {};

Plane::Plane(const Vec3f& point, const Vec3f& norm, const Material& mat) : p(point), n(norm), m(mat) {}

bool Plane::hit(const Ray& ray, HitRec& hitRec) const {
    // t = - (n · (O - P₀)) / (n · d)
    float denom = n.dot(ray.get_d());
    if (std::abs(denom) > 1e-6f) {  // avoid division by zero or near-zero
        float t = (p - ray.get_o()).dot(n) / denom;
        if (t > 0.001f && t < hitRec.tHit) {
            hitRec.tHit = t;
            hitRec.p = ray.get_o() + ray.get_d() * t;
            hitRec.n = n;
            hitRec.mat = this->m;
            hitRec.anyHit = true;
            return true;
        }
    }
    return false;
}