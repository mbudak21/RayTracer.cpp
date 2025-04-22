#include "Plane.h"

Plane::~Plane() {};

Plane::Plane(const Vec3f& point, const Vec3f& norm, const Material& mat) : p(point), n(norm), m(mat) {}

bool Plane::hit(const Ray& ray, HitRec& hitRec) const {
    // p = o + t*d | Ray
    // n.p = -D    | Plane
    // t = -(D+n.o)/n.d
    // t = (n.p-n.o)/n.d
    // t = ((p-o).n)/n.d  | final equation to solve

    Vec3f d = ray.get_d();
    Vec3f o = ray.get_o();


    float denom = n.dot(d);
    if (abs(denom) > FP_EPSILON) {  // CHeck if the ray and the plane are parallel
        float t = (p - o).dot(n) / denom;
        if (t > FP_EPSILON && t < hitRec.tHit) {
            hitRec.tHit = t;
            hitRec.p = o + d * t;
            hitRec.n = n;
            hitRec.mat = this->m;
            hitRec.anyHit = true;
            return true;
        }
    }
    return false;
}