#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"
#include "Material.h"
#include "raytrace_features.h"


class Sphere : public Object {
public:
	Vec3f c;
	float r;
public:

	virtual ~Sphere();

	Sphere(const Vec3f & cen, float rad, const Material& material);

	Sphere(const Vec3f & cen, float rad);

	bool hit(const Ray & r, HitRec & rec) const;
	void computeSurfaceHitFields(const Ray & r, HitRec & rec) const;

};

#endif