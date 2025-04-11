#include "RayTracer.h"
#include "raytrace_features.h"
#include <iostream>
#include <thread>
#include <vector>


RayTracer::RayTracer(const int w, const int h) {
    this->scene = new Scene();
    this->image = new Image(w, h);
    this->bgColor = Vec3f(0.0f, 0.0f, 0.0f);
}
RayTracer::~RayTracer() {
    delete scene;
    delete image;
}

void RayTracer::searchClosestHit(const Ray& ray, HitRec& hitRec) {
    hitRec.anyHit = false;
    hitRec.tHit = ray.tClip;
    for (int i = 0; i < this->scene->objects.size(); i++) {
        HitRec tempHit;
        tempHit.tHit = hitRec.tHit;
        if(this->scene->objects[i]->hit(ray, hitRec) && tempHit.tHit < hitRec.tHit) {
            hitRec = tempHit;
        }
    }
}

Vec3f RayTracer::getEyeRayDirection(int x, int y) {
    //Uses a fix camera looking along the negative z-axis
    static float z = -3.0f;
    static float sizeX = 4.0f; 
    static float sizeY = 3.0f; 
    static float left = -sizeX * 0.5f;
    static float top = sizeY * 0.5f;
    static float dx =  sizeX / float(this->image->getWidth());
    static float dy =  sizeY / float(this->image->getHeight());

    return Vec3f(left + x * dx, top - y * dy, z).normalize();
}

void RayTracer::fireRays() {
    int numThreads = THREAD_COUNT;
    int height = image->getHeight();
    int width = image->getWidth();
    std::vector<std::thread> threads;

    auto worker = [&](int startY, int endY) {
        for (int x = 0; x < width; ++x) {
            for (int y = startY; y < endY; ++y) {
                Ray ray;
                ray.set_d(getEyeRayDirection(x, y));
                HitRec hit;
                searchClosestHit(ray, hit);
        
                Vec3f color = hit.anyHit ? computeLighting(hit, scene) : bgColor;
                image->setPixel(x, y, color);
            }
        }
    };

    int rowsPerThread = height / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * rowsPerThread;
        int endY = (i == numThreads - 1) ? height : startY + rowsPerThread;
        threads.emplace_back(worker, startY, endY);
    }

    for (auto& t : threads) t.join();
}

bool RayTracer::isInShadow(const Vec3f& point, const Vec3f& normal, const Light* light, const Scene* scene) {
    Vec3f lightDir = (light->pos - point);
    float lightDistance = lightDir.len();
    Ray shadowRay;
    shadowRay.set_o(point + normal * 1e-4); // Avoid shadow acne
    shadowRay.set_d(lightDir.normalize());

    HitRec shadowHit;
    searchClosestHit(shadowRay, shadowHit);
    return shadowHit.anyHit && shadowHit.tHit < lightDistance;
}

Vec3f RayTracer::computeLighting(const HitRec& hit, const Scene* scene) {
    Vec3f result(0, 0, 0);
    Vec3f eye(0, 0, 0);

    #if defined(AMBIENT_LIGHTING)
        result += hit.mat.getColor() * AMBIENT_COEFF;
    #endif

    Vec3f N = hit.n;
    N.normalize();
    Vec3f V = (eye - hit.p).normalize();

    for (const auto& light : scene->lights) {
        Vec3f L = (light->pos - hit.p).normalize();

        if (isInShadow(hit.p, hit.n, light.get(), scene)) continue;

        #if defined(DIFFUSE_LIGHTING)
            float diff = std::max(0.0f, N.dot(L));
            result += light->color * hit.mat.getColor() * diff * DIFFUSE_COEFF;
        #endif

        #if defined(SPECULAR_LIGHTING)
            Vec3f R = (N * (2 * N.dot(L)) - L).normalize();
            float spec = pow(std::max(0.0f, R.dot(V)), hit.mat.shininess);
            result += light->color * spec * hit.mat.specularColor * SPECULAR_COEFF;
        #endif
    }

    return result;
}





// // Original fireRays function
// void RayTracer::fireRays() {
//     Ray ray;

//     for(int x = 0; x < this->image->getWidth(); x++) {
//         for(int y = 0; y < this->image->getHeight(); y++) {
//             ray.set_d(RayTracer::getEyeRayDirection(x, y));
//             RayTracer::searchClosestHit(ray, ray.hitRec);
//             if (ray.hitRec.anyHit) {
//                 // Get the color of the object
//                 Vec3f objColor = ray.hitRec.mat.getColor();
                
//                 //std::cout << objColor.x << " " << objColor.y << " " << objColor.z << std::endl;
                
//                 this->image->setPixel(x, y, objColor); } 
//             else {
//                 this->image->setPixel(x, y, this->bgColor); }
//         }
//     }
// }

void RayTracer::toPPM(const char* path) {
    this->image->toPPM(path);
}

void RayTracer::toBMP(const char* path) {
    this->image->toBMP(path);
}

void RayTracer::addSphere(std::shared_ptr<Sphere> sphere) {
    this->scene->addSphere(sphere);
}

void RayTracer::addLight(std::shared_ptr<Light> light){
    this->scene->addLight(light);
}


// void RayTracer::fireRays() {
//     Ray ray;
//     Vec3f Color = Vec3f(1.0f, 1.0f, 0.0f); // Color of the ray being sent
//     for(int x = 0; x < this->image->getWidth(); x++) {
//         for(int y = 0; y < this->image->getHeight(); y++) {
//             ray.d = RayTracer::getEyeRayDirection(this->image->getWidth()-x, this->image->getHeight()-y);
//             RayTracer::searchClosestHit(ray, ray.hitRec);
//             if (ray.hitRec.anyHit) {
//                 this->image->setPixel(x, y, Color); } 
//             else {
//                 this->image->setPixel(x, y, this->bgColor); }
//         }
//     }
// }