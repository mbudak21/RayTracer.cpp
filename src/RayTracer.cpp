#include "RayTracer.h"
#include "raytrace_features.h"
#include <iostream>
#include <thread>
#include <vector>


RayTracer::RayTracer(const int w, const int h) {
    this->scene = new Scene();
    this->image = new Image(w, h);
    this->bgColor = Vec3f(0.01f, 0.01f, 0.3f);
}

RayTracer::~RayTracer() {
    delete scene;
    delete image;
}

void RayTracer::searchClosestHit(const Ray& ray, HitRec& hitRec) {
    hitRec = {}; // Reset hit record
    hitRec.tHit = ray.tClip;

    for (const auto& object : scene->objects) {
        HitRec tempHit{ .tHit = hitRec.tHit }; // Initialize with current max distance
        if (object->hit(ray, tempHit) && tempHit.tHit < hitRec.tHit) {
            hitRec = tempHit;
            hitRec.anyHit = true;
        }
    }
}

Vec3f RayTracer::getEyeRayDirection(float x, float y) {
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
    int width = image->getWidth();
    int height = image->getHeight();
    std::vector<std::thread> threads;

    auto worker = [&](int startY, int endY) {
        for (int x = 0; x < width; ++x) {
            for (int y = startY; y < endY; ++y) {
                image->setPixel(x, y, samplePixel(x,y));
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

Vec3f RayTracer::samplePixel(const int x, const int y) {
    #if !defined(ANTI_ALIASING_CONST) || ANTI_ALIASING_CONST == 1
        // Don't do anti aliasing
            Ray ray;
            ray.set_d(getEyeRayDirection(x, y));
            HitRec hit;
            searchClosestHit(ray, hit);
        
            return hit.anyHit ? computeLighting(ray, hit, ray.get_d()) : bgColor;
    #endif

    float delta = 1.0 / ANTI_ALIASING_CONST;
    // printf("delta: %.2f\n", delta);

    Vec3f color_sum = Vec3f(0, 0, 0);
    for (int dx = 0; dx < ANTI_ALIASING_CONST; ++dx) {
        for (int dy = 0; dy < ANTI_ALIASING_CONST; ++dy) {
            Ray ray;
            float sample_x = randomInRange(x+(delta*dx), x+(delta*(dx+1)));
            float sample_y = randomInRange(y+(delta*dy), y+(delta*(dy+1)));
            Vec3f sample_ray_dir = getEyeRayDirection(sample_x, sample_y);
            ray.set_d(sample_ray_dir);
            HitRec hit;
            searchClosestHit(ray, hit);
        
            color_sum += hit.anyHit ? computeLighting(ray, hit, sample_ray_dir) : bgColor;

            // printf("x, y = (%.2f, %.2f)\n", sample_x, sample_y);
        }
    }

    color_sum.x /= (ANTI_ALIASING_CONST*ANTI_ALIASING_CONST); // Didn't wanna import pow()
    color_sum.y /= (ANTI_ALIASING_CONST*ANTI_ALIASING_CONST);
    color_sum.z /= (ANTI_ALIASING_CONST*ANTI_ALIASING_CONST);

    return color_sum;
}

float RayTracer::randomInRange(float a, float b) {
    return a + ((rand() % 10000) / 10000.0f) * (b - a);
}


bool RayTracer::hitsAnything(const Ray& ray){
    HitRec hit = ray.hitRec;

    for (const auto& object : scene->objects) {
        if (object->hit(ray, hit) && hit.tHit < ray.tMax) {
            return true;
        }
    }
    return false;
}

bool RayTracer::isInShadow(const Vec3f& point, const Vec3f& N, const Light* light){
    // check if the given point is in the shadow of the given light
    Vec3f shadowOrigin = point + N * 0.0001f;
    Vec3f shadowDir = (light->pos - shadowOrigin).normalize();
    Ray shadowRay = Ray(shadowOrigin, shadowDir);

    HitRec shadowHit;
    searchClosestHit(shadowRay, shadowHit);

    // The line below makes sure hits after the light source are not counted.
    return shadowHit.anyHit && shadowHit.tHit < (light->pos - point).len();
}

Vec3f RayTracer::computeLighting(const Ray& ray, const HitRec& hit, const Vec3f& origin) {    
    return computeLighting(ray, hit, origin, 0);
}


Vec3f RayTracer::computeLighting(const Ray& ray, const HitRec& hit, const Vec3f& origin, int depth) {
    //fprintf(stdout, "\ndepth: %d", depth);
    if (depth > MAX_RECURSION_DEPTH) return bgColor;

    Vec3f result(0, 0, 0); // value to be returned

    Vec3f N = hit.n;
    N.normalize();
    Vec3f V = (origin - hit.p).normalize();

    float shadowWeight = 1.0f;
    bool seenLight = false;

    #if defined(AMBIENT_LIGHTING)
        Vec3f ambient = hit.mat.getAmbient();
        result += ambient;
    #endif

    for (const auto& light : scene->lights) {
        #if defined(SHADOWS_BLACK) || defined(SHADOWS_AMBIENT)
            bool inShadow = this->isInShadow(hit.p, N, light.get());
            seenLight = inShadow ? seenLight : true;
            
            #ifdef SHADOWS_BLACK
                shadowWeight = inShadow ? 0 : 1;
            #else // SHADOWS_AMBIENT
                shadowWeight = inShadow ? 0 : 1;
                if (inShadow) continue;  // ambient-only already added; skip other lighting
            #endif
        #endif

        // Direction from the hit point to the light source
        Vec3f L = (light->pos - hit.p).normalize();

        #if defined(DIFFUSE_LIGHTING)
            float diff = std::max(0.0f, N.dot(L));
            result += light->getDiffuse() * hit.mat.getDiffuse() * diff * shadowWeight;
        #endif

        #if defined(SPECULAR_LIGHTING)
            Vec3f R = (N * (2 * N.dot(L)) - L).normalize();
            float spec = pow(std::max(0.0f, R.dot(V)), hit.mat.shininess);
            result += light->getSpecular() * spec * hit.mat.getSpecular() * shadowWeight;
        #endif
    }

    #if defined(REFLECTIONS)
    if (hit.mat.getRef() > 0.0f) { 
        // R = V - N(V.N)*2
        #if defined(FUZZY_NORMALS)
            Vec3f fuzz = Vec3f(
                (rand() % 2000) / 2000.0f - 1.0f,
                (rand() % 2000) / 2000.0f - 1.0f,
                (rand() % 2000) / 2000.0f - 1.0f
            );
            Vec3f R = (V - (N*V.dot(N))*2).normalize();
            R = R + fuzz * hit.mat.fuzz;
            R.normalize();
        #else
            Vec3f R = (V - (N*V.dot(N))*2).normalize();
        #endif

        Ray refRay(hit.p + N * 0.005f, -R); // Offset a bit to avoid self-hit
        HitRec refHit;
        searchClosestHit(refRay, refHit);

        if (refHit.anyHit) {
            // Shoot a ray from the hitPoint, in dir R
            Vec3f refColor = computeLighting(ray, refHit, hit.p + N * 0.005f, depth + 1);
            result = result * (1.0f - hit.mat.ref) + refColor * hit.mat.ref;
        } else {
            result = result * (1.0f - hit.mat.ref) + bgColor * hit.mat.ref;
        }
    }
    #endif


    #if defined(REFRACTIONS)
    if (hit.mat.getTrnsp() > 0.0f) {
        Vec3f T = (V - (N*V.dot(N))*2).normalize();
        Ray trRay(hit.p - N * 0.005f, T); // Offset a bit to avoid self-hit
        HitRec trHit;
        searchClosestHit(trRay, trHit);

        if (trHit.anyHit) {
            // Shoot a ray from the hitPoint, in dir T
            Vec3f trColor = computeLighting(ray, trHit, hit.p - N * 0.005f, depth + 1);
            result = result * (1.0f - hit.mat.trnsp) + trColor * hit.mat.trnsp;
        } else {
            result = result * (1.0f - hit.mat.trnsp) + bgColor * hit.mat.trnsp;
        }
    }
    #endif

    #if defined(SHADOWS_BLACK)
        if (!seenLight) { // is in pure shadow
            result = Vec3f(0, 0, 0);
        }
    #endif

    return Vec3f( // Clamp
        std::min(1.0f, std::max(0.0f, result.x)),
        std::min(1.0f, std::max(0.0f, result.y)),
        std::min(1.0f, std::max(0.0f, result.z))
    );
}

// Ray RayTracer::getRefrRay(){
//     // Snells formula:
//     // n_1*​sin(θ_1) ​= n_2*​sin(θ_2)
// }



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

// void RayTracer::addSphere(std::shared_ptr<Sphere> sphere) {
//     this->scene->addSphere(sphere);
// }

void RayTracer::addObj(std::shared_ptr<Object> obj) {
    this->scene->addObj(obj);
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
