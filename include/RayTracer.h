#ifndef _RayTracer_H_
#define _RayTracer_H_

#include "Scene.h"
#include "Image.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include "Light.h"
#include "Plane.h"
#include "Triangle.h"

class RayTracer {
private: 
	Scene * scene;
	Image * image;
    Vec3f bgColor;

public:
    RayTracer(const int w, const int h);
    ~RayTracer();
    void searchClosestHit(const Ray & ray, HitRec & hitRec);
	Vec3f getEyeRayDirection(float x, float y);
    void fireRays();
    void toPPM(const char* path);
    void toBMP(const char* path);
    // void addSphere(std::shared_ptr<Sphere> sphere);
    void addObj(std::shared_ptr<Object> obj);
	void addLight(std::shared_ptr<Light> light);

    bool hitsAnything(const Ray& ray);
    bool isInShadow(const Vec3f& point, const Vec3f& N, const Light* light);
    Vec3f computeLighting(const Ray& ray, const HitRec& hit, const Vec3f& origin);
    Vec3f computeLighting(const Ray& ray, const HitRec& hit, const Vec3f& origin, float refr_index, int depth);
    Ray getRefrRay(float n1, float n2, const Vec3f& N, const Vec3f& IncomingRayDir, const Vec3f& hitPoint);
    Vec3f samplePixel(const int x, const int y);
    float randomInRange(float a, float b);
    void loadScene(int scene);


    // bool isInShadow(const Vec3f& point, const Vec3f& normal, const Light* light, const Scene* scene);
};

#endif