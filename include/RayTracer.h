#ifndef _RayTracer_H_
#define _RayTracer_H_

#include "Scene.h"
#include "Image.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include "Light.h"
#include "Plane.h"

class RayTracer {
private: 
	Scene * scene;
	Image * image;
    Vec3f bgColor;

public:
    RayTracer(const int w, const int h);
    ~RayTracer();
    void searchClosestHit(const Ray & ray, HitRec & hitRec);
	Vec3f getEyeRayDirection(int x, int y);
    void fireRays();
    void toPPM(const char* path);
    void toBMP(const char* path);
    // void addSphere(std::shared_ptr<Sphere> sphere);
    void addObj(std::shared_ptr<Object> obj);
	void addLight(std::shared_ptr<Light> light);

    bool hitsAnything(const Ray& ray);
    bool isInShadow(const Vec3f& point, const Vec3f& N, const Light* light);
    Vec3f computeLighting(const HitRec& hit);
    Vec3f computeLighting(const HitRec& hit, int depth);



    // bool isInShadow(const Vec3f& point, const Vec3f& normal, const Light* light, const Scene* scene);
};

#endif