#include "Sphere.h"
#include <cassert>

Sphere::~Sphere() {}

Sphere::Sphere(const Vec3f & cen, float rad, const Material& material) : c(cen), r(rad) { 
	mat = material; // inherited from Object
}

// Sphere::Sphere(const Vec3f & cen, float rad) : c(cen), r(rad) {

// 	Color col = Color(Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f))

// 	mat = Material(col); // default red
// }

bool Sphere::hit(const Ray & r, HitRec & rec) const {
	// Circle
	Vec3f c_c = this->c;
	float c_r = this->r;

	// Ray
	Vec3f r_o = r.get_o();
	Vec3f r_d = r.get_d();

	float A = 1.0f; // Comes from r_d.dot(r_d); no need for sanity check since it should be guaranteed
	Vec3f L = r_o - c_c;
	float B = 2.0f * L.dot(r_d);
	float C = L.dot(L) - c_r * c_r;

	float delta = B*B - 4*A*C;

	if (delta < 0) return false;

	float sqrt_d = sqrt(delta);

	float t = (-B - sqrt_d) / (2*A); // Closer solution

    if (t < Ray::rayEps) {
        t = (-B + sqrt_d) / (2 * A); // Use the further solution
        if (t < Ray::rayEps) return false; // If its still behind, return false
    }

	if (t >= rec.tHit) return false; // something closer already

    // Record the hit
    rec.anyHit = true;
    rec.tHit = t;
    rec.p = r_o + r_d * t;
    rec.n = (rec.p - c_c).normalize();
    rec.mat = this->mat;

	return true;
}

// bool Sphere::hit(const Ray & r, HitRec & rec) const {
// 	// c: center of sphere
// 	// r: radius	
// 	Vec3f r_o = r.get_o();
// 	Vec3f r_d = r.get_d();

// 	Vec3f v = c - r_o; // vector from r.o to sphere center
// 	float s = v.dot(r_d); // projection of v onto d
// 	float vLenSq = v.dot(v); //
// 	float radSq = this->r * this->r; 
// 	if (s < 0 && vLenSq > radSq) {
// 		return false;
// 	}
// 	float mSq = vLenSq - s * s;
// 	if (mSq > radSq) {
// 		return false;
// 	}

// 	rec.anyHit = true;
// 	rec.mat = this->mat;
// 	return true;
// }


void Sphere::computeSurfaceHitFields(const Ray & r, HitRec & rec) const {
	rec.p = r.get_o() + r.get_d() * rec.tHit;
	rec.n = (rec.p - c).normalize();
}
