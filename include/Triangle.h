#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"
#include "Material.h"
#include "raytrace_features.h"


class Triangle : public Object {
private:
	Vec3f N;
    bool hasNormal; // For optimization
public:
	Vec3f p1;
	Vec3f p2;
	Vec3f p3;
    Material m;
public:

	virtual ~Triangle();

    Triangle(const Vec3f& p1, const Vec3f& p2, const Vec3f& p3);
	Triangle(const Vec3f& p1, const Vec3f& p2, const Vec3f& p3, const Material& material);

    Vec3f getN() const;

	bool hit(const Ray& r, HitRec& rec) const;
	//void computeSurfaceHitFields(const Ray & r, HitRec & rec) const;

};

#endif