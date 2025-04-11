#include "RayTracer.h"

#include "Vec3.h" 
#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1200
RayTracer* initTracer(int width, int height)
{
	RayTracer* rayTracer = new RayTracer(width, height);

	// Materials
	auto m1 = Material(Vec3f(1.0f, 0.0f, 0.0f));
	m1.specularColor = Vec3f(1, 1, 1);
	m1.shininess = 100;
	auto m2 = Material(Vec3f(0.0f, 1.0f, 0.0f));
	m2.specularColor = Vec3f(1, 1, 1);
	m2.shininess = 100;
	auto m3 = Material(Vec3f(1.0f, 1.0f, 0.2f));
	m3.specularColor = Vec3f(1, 1, 1);
	m3.shininess = 100;

	// Lights
	auto light_1 = std::make_shared<Light>(Vec3f(100.0f, 15.0f, -5.0f), Vec3f(1.0f, 1.0f, 1.0f));
	auto light_2 = std::make_shared<Light>(Vec3f(0.0f, -15.0f, +25.0f), Vec3f(1.0f, 0.2f, 1.0f));
	
	// Spheres
	auto s1 = std::make_shared<Sphere>(Vec3f(0.0f, 0.0f, -25.0f), 1.0f, m1);
	auto s2 = std::make_shared<Sphere>(Vec3f(2.0f, 0.0f, -25.0f), 1.0f, m2);
	auto s3 = std::make_shared<Sphere>(Vec3f(4.0f, 0.0f, -25.0f), 1.0f, m3);

	
	rayTracer->addLight(light_1);
	rayTracer->addLight(light_2);
	rayTracer->addSphere(s1);
	rayTracer->addSphere(s2);
	rayTracer->addSphere(s3);

	


	return rayTracer;
}

void runTracer(RayTracer* tracer)
{
	tracer->fireRays();
	tracer->toPPM("DVA338_Raytracer_output.ppm");
	tracer->toBMP("DVA338_Raytracer_output.bmp");
}

void destroyTracer(RayTracer* tracer)
{
	delete tracer;
}

int main(int argc, char **argv) {
	RayTracer* tracer = initTracer(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	runTracer(tracer);
	destroyTracer(tracer);
	return 0;
}
