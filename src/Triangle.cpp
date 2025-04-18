#include "Triangle.h"

Triangle::~Triangle() {};

Triangle::Triangle(const Vec3f& p1, const Vec3f& p2, const Vec3f& p3, const Material& mat) : p1(p1), p2(p2), p3(p3), m(mat) {}

bool Triangle::hit(const Ray& ray, HitRec& hitRec) const {
    // p = o + t*d | Ray
    Vec3f d = ray.get_d();
    Vec3f o = ray.get_o();

    // N.p1 = -D    | Plane
    Vec3f N = this->get_N();
    float D = -N.dot(this->p1);


    float denom = N.dot(d);
    if (abs(denom) > PLANE_FP_EPS) {  // Check if the ray and the plane are parallel
        float t = (p1 - o).dot(N) / denom;
        if (t > 0.001f && t < hitRec.tHit) { // Hits the plane, and is in front of the ray
            Vec3f hitPoint = o + d * t;

            

            // hitRec.tHit = t;
            // hitRec.p = o + d * t;
            // hitRec.n = N;
            // hitRec.mat = this->m;
            // hitRec.anyHit = true;
            // return true;
        }
    }
    return false;
}


Vec3f Triangle::get_N() const {
    Vec3f u = p2 - p1;
    Vec3f v = p3 - p1;
    return u.cross(v).normalize();
}