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

    // N.(o + t*d) = -D    | Plane Hit Check
    // No + tdO = -D
    // tdO = -D -No
    // t = (-D -No)/(dO)
    // t = (N.p1 -No)/(dO)
    // t = N(p1-o)/dO

    

    float denom = N.dot(d);
    if (denom >= 0) return false; // backface, skip
    if (abs(denom) > FP_EPSILON) {  // Check if the ray and the plane are parallel
        float t = (p1 - o).dot(N) / denom;
        if (t > FP_EPSILON && t < hitRec.tHit) { // Hits the plane, and is in front of the ray
            Vec3f hitPoint = o + d * t; 
            // Inside-triangle check using barycentric coordinates
            Vec3f v0 = p2 - p1;
            Vec3f v1 = p3 - p1;
            Vec3f v2 = hitPoint - p1;

            float dot00 = v0.dot(v0);
            float dot01 = v0.dot(v1);
            float dot02 = v0.dot(v2);
            float dot11 = v1.dot(v1);
            float dot12 = v1.dot(v2);

            float denom = dot00 * dot11 - dot01 * dot01;
            if (fabs(denom) < FP_EPSILON) return false; // degenerate triangle

            float invDenom = 1.0f / denom;
            float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
            float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

            if (u >= 0 && v >= 0 && (u + v) <= 1) {
                hitRec.tHit = t;
                hitRec.p = hitPoint;
                hitRec.n = N;
                hitRec.mat = this->m;
                hitRec.anyHit = true;
                return true;
            }
            

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