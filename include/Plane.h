#ifndef _PLANE_H_
#define _PLANE_H_

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"
#include "Material.h"
#include "raytrace_features.h"


class Plane : public Object {
public:
	Vec3f p;
	Vec3f n;
    Material m;
public:

	virtual ~Plane();

	Plane(const Vec3f& p, const Vec3f& n, const Material& material);
	Plane(const Vec3f& p, const Vec3f& n);

	bool hit(const Ray& r, HitRec& rec) const;
	//void computeSurfaceHitFields(const Ray & r, HitRec & rec) const;

};

#endif