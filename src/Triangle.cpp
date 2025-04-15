#include "Triangle.h"

Triangle::~Triangle() {};

Triangle::Triangle(const Vec3f& p1, const Vec3f& p2, const Vec3f& p3, const Material& mat) : p1(p1), p2(p2), p3(p3), m(mat) {}

bool Triangle::hit(const Ray& ray, HitRec& hitRec) const {
    // Vec3f O = ray.get_o();
    // Vec3f D = ray.get_d();

    // Vec3f v0 = p1;
    // Vec3f v1 = p2;
    // Vec3f v2 = p3;

    // // Find edges of the triangle
    // Vec3f edge1 = v1 - v0;
    // Vec3f edge2 = v2 - v0;

    // // Begin calculating determinant - also used to calculate u parameter
    // Vec3f h = D.cross(edge2).normalize();
    // float a = edge1.dot(h);

    // // If a is close to 0, the ray is parallel to the triangle
    // if (fabs(a) < 0.00001f) {
    //     hitRec.anyHit = false;
    //     return false;
    // }

    // float f = 1.0f / a;
    // Vec3f s = O - v0;
    // float u = f * s.dot(h);

    // // Check if the intersection is outside the triangle
    // if (u < 0.0f || u > 1.0f) {
    //     hitRec.anyHit = false;
    //     return false;
    // }


    // Vec3f q = s.cross(edge1);
    // float v = f * D.dot(q);

    // if (v < 0.0f || u + v > 1.0f){
    //     hitRec.anyHit = false;
    //     return false;
    // }

    // float t = f * edge2.dot(q);

    // if (t > ray.tClip){
    //     hitRec.anyHit = false;
    //     return false;
    // }


    // // We have a hit
    // hitRec.tHit = t;
    // hitRec.p = O + D * t;
    // hitRec.n = getN();
    // hitRec.mat = this->mat;
    // hitRec.anyHit = true;

    return false;
}


Vec3f Triangle::getN() const {
    Vec3f u = p2 - p1;
    Vec3f v = p3 - p1;
    return u.cross(v).normalize();
}