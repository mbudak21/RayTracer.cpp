#include "RayTracer.h"
#include "raytrace_features.h"
#include "Defaults.h"

#include <iostream>
#include <thread>
#include <vector>


RayTracer::RayTracer(const int w, const int h) {
    this->scene = new Scene();
    this->image = new Image(w, h);
    // R:  40, G:  41, B:  45
    this->bgColor = Vec3f(55.0f/256.0f, 56.0f/256.0f, 55.0f/256.0f);
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
    /*
    Each thread is responsible for rendering a horizontal strip of the image.
    Example: If the image height is 400px, and there are 4 threads, each thread will render 100 pixels.
    The last thread picks up any remaining pixels if the height is not divisible by the number of threads. (line 70 "int endY...")
    */
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
        threads.emplace_back(worker, startY, endY); // Create a thread for each strip
    }

    for (auto& t : threads) t.join(); // Wait for all threads to finish
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
    Vec3f shadowOrigin = point + N * FP_EPSILON;
    Vec3f shadowDir = (light->pos - shadowOrigin).normalize();
    Ray shadowRay = Ray(shadowOrigin, shadowDir);

    HitRec shadowHit;
    searchClosestHit(shadowRay, shadowHit);

    // The line below makes sure hits after the light source are not counted.
    return shadowHit.anyHit && shadowHit.tHit < (light->pos - point).len();
}

Vec3f RayTracer::computeLighting(const Ray& ray, const HitRec& hit, const Vec3f& origin) {    
    return computeLighting(ray, hit, origin, 1.0f, 0); // Assume air in refr_index=1.0
}


Vec3f RayTracer::computeLighting(const Ray& ray, const HitRec& hit, const Vec3f& origin, float refr_index, int depth) {
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
                (rand() % 2000) / 2000.0f - 0.5f,
                (rand() % 2000) / 2000.0f - 0.5f,
                (rand() % 2000) / 2000.0f - 0.5f
            );
            Vec3f R = (V - (N*V.dot(N))*2).normalize();
            R = R + fuzz * hit.mat.fuzz;
            R.normalize();
        #else
            Vec3f R = (V - (N*V.dot(N))*2).normalize();
        #endif

        Ray refRay(hit.p + N * FP_EPSILON, -R); // Offset a bit to avoid self-hit
        HitRec refHit;
        searchClosestHit(refRay, refHit);

        if (refHit.anyHit) {
            // Shoot a ray from the hitPoint, in dir R
            Vec3f refColor = computeLighting(ray, refHit, hit.p + N * FP_EPSILON, hit.mat.getRefrIndex(), depth + 1);
            result = result * (1.0f - hit.mat.ref) + refColor * hit.mat.ref;
        } else {
            result = result * (1.0f - hit.mat.ref) + bgColor * hit.mat.ref;
        }
    }
    #endif


    #if defined(REFRACTIONS)
    if (hit.mat.getTrnsp() > 0.0f) {
        Ray trRay = getRefrRay(refr_index, hit.mat.refrIndex, N, ray.get_d(), hit.p);
        HitRec trHit;
        searchClosestHit(trRay, trHit);

        if (trHit.anyHit) {
            // Shoot a ray from the hitPoint, in dir T
            Vec3f trColor = computeLighting(trRay, trHit, hit.p - N * FP_EPSILON, hit.mat.refrIndex, depth + 1);
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

Ray RayTracer::getRefrRay(float n1, float n2, const Vec3f& N, const Vec3f& IncomingRayDir, const Vec3f& hitPoint) {
    Vec3f I = IncomingRayDir;
    Vec3f normal = N;

    // Determine if we are entering or exiting
    float cosI = I.dot(normal);
    if (cosI > 0.0f) {
        // We're inside the object, so invert the normal and swap indices
        std::swap(n1, n2);
        normal = -normal;
        cosI = I.dot(normal); // recalculate after flipping normal
    }

    float eta = n1 / n2;
    float cosThetaI = -cosI;
    float sin2T = eta * eta * (1.0f - cosThetaI * cosThetaI);

    if (sin2T > 1.0f) {
        // Total internal reflection
        Vec3f reflectDir = I - (normal * 2.0f * I.dot(normal));
        return Ray(hitPoint + normal * FP_EPSILON, reflectDir.normalize());
    }

    float cosThetaT = sqrtf(1.0f - sin2T);
    Vec3f refrDir = (I + (normal * (eta * cosThetaI - cosThetaT))) * eta;
    return Ray(hitPoint - normal * FP_EPSILON, refrDir.normalize());
}



void RayTracer::toPPM(const char* path) {
    this->image->toPPM(path);
}

void RayTracer::toBMP(const char* path) {
    this->image->toBMP(path);
}

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


void RayTracer::loadScene(int scene) {
    printf("Loading scene %i. \n", scene);
    if (scene == 131 || scene == 132 || scene == 133 || scene == 134 || scene == 140 || scene == 150) {
        // Red sphere on the left, green sphere on the right, blue plane as ground.
        Vec3f light_pos = Vec3f(-13.0f, 15.0f, -5.0f);
        Vec3f red_sphere_pos = Vec3f(0.0f, 0.0f, -15.0f);
        Vec3f green_sphere_pos = Vec3f(2.0f, -0.1f, -15.0f);

        auto light_1 = std::make_shared<Light>(light_pos, ColorDefaults::White);
        auto red_sphere = std::make_shared<Sphere>(red_sphere_pos, 1.0f, MaterialDefaults::RedRealistic);
        auto green_sphere = std::make_shared<Sphere>(green_sphere_pos, 0.9f, MaterialDefaults::GreenRealistic);
        auto plane = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), MaterialDefaults::BlueRealistic);

        this->addLight(light_1);
        this->addObj(red_sphere);
        this->addObj(plane);
        this->addObj(green_sphere);
    }
    if (scene == 211){
        // Red sphere on the left, green sphere on the right, blue plane as ground.

        // Positions
        Vec3f light_pos = Vec3f(-10.0f, 20.0f, -10.0f);
        Vec3f red_sphere_pos = Vec3f(0.0f, 0.0f, -15.0f);
        Vec3f green_sphere_pos = Vec3f(2.0f, -0.1f, -15.0f);

        // Colors
        const Color Red_col(Vec3f(0.1f, 0.0f, 0.0f), Vec3f(0.5f, 0.03f, 0.03f), Vec3f(0.3f, 0.3f, 0.0f));
        const Color Green_col(Vec3f(0.0f, 0.1f, 0.0f), Vec3f(0.03f, 0.5f, 0.03f), Vec3f(0.3f, 0.3f, 0.0f));

        // Materials
        const Material Red_mat(Red_col, 0.2f);
        const Material Green_mat(Green_col, 0.7f);

        auto light_1 = std::make_shared<Light>(light_pos, ColorDefaults::White);
        auto red_sphere = std::make_shared<Sphere>(red_sphere_pos, 1.0f, Red_mat);
        auto green_sphere = std::make_shared<Sphere>(green_sphere_pos, 0.9f, Green_mat);
        auto plane = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), MaterialDefaults::Mirror);

        this->addLight(light_1);
        this->addObj(red_sphere);
        this->addObj(plane);
        this->addObj(green_sphere);
    }
    if (scene == 220 | scene == 230){
        // Red sphere on the left, green sphere on the right, blue plane as ground.
        // Lights
        auto light_1 = std::make_shared<Light>(Vec3f(-9.0f, 15.0f, -20.0f), ColorDefaults::White);
        auto light_2 = std::make_shared<Light>(Vec3f(13.0f, 15.0f, -20.0f), ColorDefaults::White);

        Color red(Vec3f(0.0f, 0.0f, 0.1f), Vec3f(0.9f, 0.0f, 0.0f), Vec3f(0.6f, 0.6f, 0.0f));
        Material redC(red, 20.f/128.0f, 0.7f);
        redC.fuzz = 0.05f;
        redC.trnsp = 0.5f;

        Color green(Vec3f(0.0f, 0.0f, 0.1f), Vec3f(0.0f, 0.9, 0.0f), Vec3f(0.6f, 0.6f, 0.0f));
        Material greenC(green, 20.f, 0.7f);
        greenC.fuzz = 0.05f;
        greenC.trnsp = 0.0f;


        auto s1 = std::make_shared<Sphere>(Vec3f(0.0f, 1.0f, -25.0f), 2.0f, redC);
        auto s2 = std::make_shared<Sphere>(Vec3f(5.0f, 1.0f, -25.0f), 2.0f, greenC);
        auto s3 = std::make_shared<Sphere>(Vec3f(-15.0f, 1.0f, -12.0f), 10.0f, MaterialDefaults::Gold);


        auto h = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), MaterialDefaults::Mirror);

        
        Vec3f A1(-6.0f, 13.0f, -28.0f); // Top left
        Vec3f A2(4.0f, 13.0f, -28.0f); // Top right
        Vec3f B(-1.0f, 13.0f, -28.0f); // top middle
        Vec3f C(-1.0f, 3.0f, -28.0f); // bottom middle

        auto t1 = std::make_shared<Triangle>(A1, C, B, redC);
        auto t2 = std::make_shared<Triangle>(C, A2, B, greenC);

        Vec3f Top(0.0f, 4.0f, -40.0f);
        Vec3f BottomLeft(-3.0f, 0.0f, -45.0f);
        Vec3f BottomRight(3.0f, 0.0f, -40.0f);
        Vec3f BottomMiddle(0.0f, 0.0f, -35.0f);

        auto t3 = std::make_shared<Triangle>(Top, BottomLeft, BottomMiddle, redC);
        auto t4 = std::make_shared<Triangle>(BottomMiddle, BottomRight, Top, greenC);

        this->addLight(light_1);
        // this->addLight(light_2);
        this->addObj(s1);
        this->addObj(s2);
        this->addObj(s3);
        this->addObj(h);
        this->addObj(t1);
        this->addObj(t2);
        this->addObj(t3);
        this->addObj(t4);
    }

    if (scene == 901){
        // Red sphere on the left, green sphere on the right, blue plane as ground.
        // Lights
        auto light_1 = std::make_shared<Light>(Vec3f(-9.0f, 15.0f, -20.0f), ColorDefaults::White);
        auto light_2 = std::make_shared<Light>(Vec3f(13.0f, 15.0f, -20.0f), ColorDefaults::White);

        Color red(Vec3f(0.0f, 0.0f, 0.1f), Vec3f(0.9f, 0.0f, 0.0f), Vec3f(0.6f, 0.6f, 0.0f));
        Material redC(red, 20.f/128.0f, 0.7f);
        redC.fuzz = 0.05f;
        redC.trnsp = 0.9f;
        redC.refrIndex = 4.5f;

        Color green(Vec3f(0.0f, 0.0f, 0.1f), Vec3f(0.0f, 0.9, 0.0f), Vec3f(0.6f, 0.6f, 0.0f));
        Material greenC(green, 20.f, 0.7f);
        greenC.fuzz = 0.05f;
        greenC.trnsp = 0.0f;


        auto s1 = std::make_shared<Sphere>(Vec3f(0.0f, 1.0f, -25.0f), 2.0f, redC);
        auto s2 = std::make_shared<Sphere>(Vec3f(5.0f, 1.0f, -25.0f), 2.0f, greenC);
        auto s3 = std::make_shared<Sphere>(Vec3f(-15.0f, 1.0f, -12.0f), 10.0f, MaterialDefaults::Gold);


        auto h = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), MaterialDefaults::Mirror);

        
        Vec3f A1(-6.0f, 13.0f, -28.0f); // Top left
        Vec3f A2(4.0f, 13.0f, -28.0f); // Top right
        Vec3f B(-1.0f, 13.0f, -28.0f); // top middle
        Vec3f C(-1.0f, 3.0f, -28.0f); // bottom middle

        auto t1 = std::make_shared<Triangle>(A1, C, B, redC);
        auto t2 = std::make_shared<Triangle>(C, A2, B, greenC);

        Vec3f Top(0.0f, 4.0f, -40.0f);
        Vec3f BottomLeft(-3.0f, 0.0f, -45.0f);
        Vec3f BottomRight(3.0f, 0.0f, -40.0f);
        Vec3f BottomMiddle(0.0f, 0.0f, -35.0f);

        auto t3 = std::make_shared<Triangle>(Top, BottomLeft, BottomMiddle, redC);
        auto t4 = std::make_shared<Triangle>(BottomMiddle, BottomRight, Top, greenC);

        this->addLight(light_1);
        // this->addLight(light_2);
        this->addObj(s1);
        this->addObj(s2);
        this->addObj(s3);
        this->addObj(h);
        this->addObj(t1);
        this->addObj(t2);
        this->addObj(t3);
        this->addObj(t4);
    }

    if (scene == 902){
        // Lights
        auto light_1 = std::make_shared<Light>(Vec3f(-9.0f, 15.0f, -20.0f), ColorDefaults::White);
        auto light_2 = std::make_shared<Light>(Vec3f(13.0f, 15.0f, -20.0f), ColorDefaults::White);
        
        // Spheres
        auto s1 = std::make_shared<Sphere>(Vec3f(-18.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::BlackFlat);
        auto s2 = std::make_shared<Sphere>(Vec3f(-15.0f, 0.5f, -55.0f), 1.5f, MaterialDefaults::WhiteFlat);
        auto s3 = std::make_shared<Sphere>(Vec3f(-12.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::Gold);
        auto s4 = std::make_shared<Sphere>(Vec3f(-9.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::Copper);
        auto s5 = std::make_shared<Sphere>(Vec3f(-6.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::Silver);
        auto s6 = std::make_shared<Sphere>(Vec3f(-3.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::Obsidian);
        auto s7 = std::make_shared<Sphere>(Vec3f(0.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::Ruby);
        auto s8 = std::make_shared<Sphere>(Vec3f(3.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::Chrome);
        auto s9 = std::make_shared<Sphere>(Vec3f(6.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::WhitePlastic);
        auto s10 = std::make_shared<Sphere>(Vec3f(9.0f, 0.5f, -55.0f), 1.5f, MaterialDefaults::BlackPlastic);
        auto s11 = std::make_shared<Sphere>(Vec3f(12.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::WhiteRubber);
        auto s12 = std::make_shared<Sphere>(Vec3f(15.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::BlackRubber);
        auto s13 = std::make_shared<Sphere>(Vec3f(18.0f, 1.0f, -55.0f), 1.5f, MaterialDefaults::CyanPlastic);

        // Triangles
        Vec3f A1(1.0f, 5.0f, -35.0f);
        Vec3f B1(4.0f, 5.0f, -35.0f);
        Vec3f C1(4.0f, 8.0f, -35.0f);

        Vec3f A2(-4.0f, 5.0f, -35.0f);
        Vec3f B2(-1.0f, 5.0f, -35.0f);
        Vec3f C2(-1.0f, 8.0f, -35.0f);
        auto t1 = std::make_shared<Triangle>(A1, B1, C1, MaterialDefaults::Chrome);
        auto t2 = std::make_shared<Triangle>(A2, C2, B2, MaterialDefaults::Ruby);

        // Horizontal Plane
        auto h = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), MaterialDefaults::Mirror);
        
        this->addLight(light_1);
        this->addLight(light_2);
        
        this->addObj(s1);
        this->addObj(s2);
        this->addObj(s3);
        this->addObj(s4);
        this->addObj(s5);
        this->addObj(s6);
        this->addObj(s7);
        this->addObj(s8);
        this->addObj(s9);
        this->addObj(s10);
        this->addObj(s11);
        this->addObj(s12);
        this->addObj(s13);

        this->addObj(t1);
        this->addObj(t2);
        this->addObj(h);

        printf("s1: %.2f, %.2f\n", s1->getMaterial().getShine(), s1->getMaterial().getRef());
        printf("s2: %.2f, %.2f\n", s2->getMaterial().getShine(), s2->getMaterial().getRef());
        printf("s3: %.2f, %.2f\n", s3->getMaterial().getShine(), s3->getMaterial().getRef());
        printf("s4: %.2f, %.2f\n", s4->getMaterial().getShine(), s4->getMaterial().getRef());
        printf("s5: %.2f, %.2f\n", s5->getMaterial().getShine(), s5->getMaterial().getRef());
        printf("s6: %.2f, %.2f\n", s6->getMaterial().getShine(), s6->getMaterial().getRef());
        printf("s7: %.2f, %.2f\n", s7->getMaterial().getShine(), s7->getMaterial().getRef());
        printf("s8: %.2f, %.2f\n", s8->getMaterial().getShine(), s8->getMaterial().getRef());

        // printf("Ref: %.2f, %.2f\n", t1->getMaterial().getShine(), t1->getMaterial().getRef());
        printf("Ref: %.2f, %.2f\n", h->getMaterial().getShine(), h->getMaterial().getRef());
        

        // rayTracer->addSphere(s3);
    }

}
