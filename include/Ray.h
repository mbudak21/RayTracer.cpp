#ifndef _RAY_H_
#define _RAY_H_

#include "Vec3.h"
#include "Material.h"
#include "cassert"
#include "raytrace_features.h"


struct HitRec {
	float tHit;
	int primIndex;
	Vec3f p;
	Vec3f n;
	bool anyHit;
	Material mat;
};

class Ray {
	private:
		Vec3f o; // origin, when the ray moves, change o by d.
		Vec3f d; // direction
	public:
		float tClip; // hit distance
		static float rayEps; // ? iteration value (set at compile) 
		static float tMax; // ? Maximal raytrace distance (set at compile)
		HitRec hitRec;
	public:
		//Default constructor: Set the start position of the eye rays to the origin
		Ray();

		Ray(const Vec3f & o, const Vec3f& d, float tclip);
		Ray(const Vec3f & o, const Vec3f& d);
		
		void epsMoveStartAlongSurfaceNormal(const Vec3f & n); // moves along vector n instead of d
		void epsMoveStartAlongDir();
		
		static void incRayEps();
		static void decRayEps();

		void set_o(const Vec3f& vec);
		const Vec3f& get_o() const;

		void set_d(const Vec3f& vec);
		const Vec3f& get_d() const;
	};
#endif
