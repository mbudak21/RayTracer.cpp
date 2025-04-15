#include "RayTracer.h"

#include "Vec3.h" 
#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1200
RayTracer* initTracer(int width, int height)
{
	RayTracer* rayTracer = new RayTracer(width, height);
	Vec3f RED = Vec3f(1.0f, 0.0f, 0.0f);
	Vec3f GREEN = Vec3f(0.0f, 1.0f, 0.0f);
	Vec3f BLUE = Vec3f(0.0f, 0.0f, 1.0f);
	Vec3f WHITE = Vec3f(1.0f, 1.0f, 1.0f);
	Vec3f BLACK = Vec3f(0.0f, 0.0f, 0.0f);

	// Materials
	auto red_shiny = Material(RED, 100, WHITE, 0.1);
	auto green_shiny = Material(GREEN, 100, WHITE, 0.4);
	auto white_shiny = Material(WHITE, 100, WHITE, 0.5);
	auto mirror = Material(WHITE, 1, WHITE, 0.2);

	// Lights
	auto light_1 = std::make_shared<Light>(Vec3f(-3.0f, 2.0f, -10.0f), Vec3f(1.0f, 1.0f, 1.0f));
	auto light_2 = std::make_shared<Light>(Vec3f(+3.0f, 1.0f, -10.0f), Vec3f(1.0f, 1.0f, 1.0f));
	
	// Spheres
	auto s1 = std::make_shared<Sphere>(Vec3f(0.0f, 0.0f, -25.0f), 1.0f, red_shiny);
	auto s2 = std::make_shared<Sphere>(Vec3f(3.0f, 1.0f, -25.0f), 2.0f, green_shiny);
	auto s3 = std::make_shared<Sphere>(Vec3f(4.0f, 0.0f, -25.0f), 1.0f, white_shiny);
	auto s4 = std::make_shared<Sphere>(Vec3f(6.0f, 0.0f, -25.0f), 1.0f, green_shiny);
	auto s5 = std::make_shared<Sphere>(Vec3f(8.0f, 0.0f, -25.0f), 1.0f, white_shiny);
	auto s6 = std::make_shared<Sphere>(Vec3f(10.0f, 0.0f, -25.0f), 1.0f, green_shiny);

	// Triangles
	Vec3f A1(0.0f, 1.0f, -15.0f);
	Vec3f B1(1.0f, 0.0f, -15.0f);
	Vec3f C1(0.0f, 0.0f, -15.0f);
	auto t1 = std::make_shared<Triangle>(C1, B1, A1, red_shiny);

	// Horizontal Plane
	auto h = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), mirror);

	//auto s3 = std::make_shared<Sphere>(Vec3f(4.0f, 0.0f, -25.0f), 1.0f, m3);

	
	rayTracer->addLight(light_1);
	rayTracer->addLight(light_2);
	rayTracer->addObj(s1);
	rayTracer->addObj(s2);
	// rayTracer->addObj(s3);
	// rayTracer->addObj(s4);
	// rayTracer->addObj(s5);
	// rayTracer->addObj(s6);
	rayTracer->addObj(t1);
	rayTracer->addObj(h);

	// rayTracer->addSphere(s3);

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
