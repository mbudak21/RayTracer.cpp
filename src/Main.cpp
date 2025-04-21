#include "RayTracer.h"
#include "Vec3.h" 
#include "Defaults.h"
#include <iostream>

// TODO:
// Use the exact scenes
// fix hitsAnything and closestHit


RayTracer* initTracer(int width, int height) {
	RayTracer* rayTracer = new RayTracer(width, height);

	// Lights
	auto light_1 = std::make_shared<Light>(Vec3f(-9.0f, 15.0f, -20.0f), ColorDefaults::White);
	auto light_2 = std::make_shared<Light>(Vec3f(13.0f, 15.0f, -20.0f), ColorDefaults::White);

	Color red(Vec3f(0.0f, 0.0f, 0.1f), Vec3f(0.9f, 0.0f, 0.0f), Vec3f(0.6f, 0.6f, 0.0f));
	Material redC(red, 20.f, 0.7f);
	redC.fuzz = 0.05f;
	redC.trnsp = 0.5f;

	Color green(Vec3f(0.0f, 0.0f, 0.1f), Vec3f(0.0f, 0.9, 0.0f), Vec3f(0.6f, 0.6f, 0.0f));
	Material greenC(green, 20.f, 0.7f);
	greenC.fuzz = 0.05f;
	greenC.trnsp = 0.0f;


	auto s1 = std::make_shared<Sphere>(Vec3f(0.0f, 1.0f, -25.0f), 2.0f, redC);
	auto s2 = std::make_shared<Sphere>(Vec3f(5.0f, 1.0f, -25.0f), 2.0f, greenC);

	auto h = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), MaterialDefaults::Mirror);

	
	Vec3f A1(-6.0f, 13.0f, -28.0f);
	Vec3f A2(4.0f, 13.0f, -28.0f);
	Vec3f B(-1.0f, 13.0f, -28.0f);
	Vec3f C(-1.0f, 3.0f, -28.0f);

	auto t1 = std::make_shared<Triangle>(A1, C, B, redC);
	auto t2 = std::make_shared<Triangle>(C, A2, B, greenC);

	Vec3f p1(-1.0f, 1.0f, -30.0f);
	Vec3f p2(1.0f, 1.0f, -30.0f);
	Vec3f p3(0.0f, 4.0f, -30.0f);

	auto t3 = std::make_shared<Triangle>(p1, p2, p3, MaterialDefaults::Chrome);

	rayTracer->addLight(light_1);
	// rayTracer->addLight(light_2);
	rayTracer->addObj(s1);
	rayTracer->addObj(s2);
	rayTracer->addObj(h);
	rayTracer->addObj(t1);
	rayTracer->addObj(t2);
	rayTracer->addObj(t3);


	return rayTracer;
}

// RayTracer* initTracer(int width, int height) {
// 	RayTracer* rayTracer = new RayTracer(width, height);


// 	// Lights
// 	auto light_1 = std::make_shared<Light>(Vec3f(-9.0f, 15.0f, -20.0f), ColorDefaults::White);
// 	auto light_2 = std::make_shared<Light>(Vec3f(13.0f, 15.0f, -20.0f), ColorDefaults::White);
	
// 	// Spheres
// 	auto s1 = std::make_shared<Sphere>(Vec3f(-18.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::FlatBlack);
// 	auto s2 = std::make_shared<Sphere>(Vec3f(-15.0f, 0.5f, -35.0f), 1.5f, MaterialDefaults::FlatWhite);
// 	auto s3 = std::make_shared<Sphere>(Vec3f(-12.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::Gold);
// 	auto s4 = std::make_shared<Sphere>(Vec3f(-9.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::Copper);
// 	auto s5 = std::make_shared<Sphere>(Vec3f(-6.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::Silver);
// 	auto s6 = std::make_shared<Sphere>(Vec3f(-3.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::Obsidian);
// 	auto s7 = std::make_shared<Sphere>(Vec3f(0.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::Ruby);
// 	auto s8 = std::make_shared<Sphere>(Vec3f(3.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::Chrome);
// 	auto s9 = std::make_shared<Sphere>(Vec3f(6.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::WhitePlastic);
// 	auto s10 = std::make_shared<Sphere>(Vec3f(9.0f, 0.5f, -35.0f), 1.5f, MaterialDefaults::BlackPlastic);
// 	auto s11 = std::make_shared<Sphere>(Vec3f(12.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::WhiteRubber);
// 	auto s12 = std::make_shared<Sphere>(Vec3f(15.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::BlackRubber);
// 	auto s13 = std::make_shared<Sphere>(Vec3f(18.0f, 1.0f, -35.0f), 1.5f, MaterialDefaults::CyanPlastic);

// 	// Triangles
// 	Vec3f A1(1.0f, 5.0f, -35.0f);
// 	Vec3f B1(4.0f, 5.0f, -35.0f);
// 	Vec3f C1(4.0f, 8.0f, -35.0f);

// 	Vec3f A2(-4.0f, 5.0f, -35.0f);
// 	Vec3f B2(-1.0f, 5.0f, -35.0f);
// 	Vec3f C2(-1.0f, 8.0f, -35.0f);
// 	auto t1 = std::make_shared<Triangle>(A1, B1, C1, MaterialDefaults::Chrome);
// 	auto t2 = std::make_shared<Triangle>(A2, C2, B2, MaterialDefaults::Ruby);

// 	// Horizontal Plane
// 	auto h = std::make_shared<Plane>(Vec3f(0.0f, -1.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f).normalize(), MaterialDefaults::Mirror);
	
// 	rayTracer->addLight(light_1);
// 	rayTracer->addLight(light_2);
	
// 	rayTracer->addObj(s1);
// 	rayTracer->addObj(s2);
// 	rayTracer->addObj(s3);
// 	rayTracer->addObj(s4);
// 	rayTracer->addObj(s5);
// 	rayTracer->addObj(s6);
// 	rayTracer->addObj(s7);
// 	rayTracer->addObj(s8);
// 	rayTracer->addObj(s9);
// 	rayTracer->addObj(s10);
// 	rayTracer->addObj(s11);
// 	rayTracer->addObj(s12);
// 	rayTracer->addObj(s13);

// 	rayTracer->addObj(t1);
// 	rayTracer->addObj(t2);
// 	rayTracer->addObj(h);

// 	printf("Ref: %.2f, %.2f\n", s1->getMaterial().getShine(), s1->getMaterial().getRef());
// 	printf("Ref: %.2f, %.2f\n", s2->getMaterial().getShine(), s2->getMaterial().getRef());
// 	printf("Ref: %.2f, %.2f\n", s3->getMaterial().getShine(), s3->getMaterial().getRef());
// 	printf("Ref: %.2f, %.2f\n", s4->getMaterial().getShine(), s4->getMaterial().getRef());
// 	printf("Ref: %.2f, %.2f\n", s5->getMaterial().getShine(), s5->getMaterial().getRef());
// 	printf("Ref: %.2f, %.2f\n", s6->getMaterial().getShine(), s6->getMaterial().getRef());

// 	// printf("Ref: %.2f, %.2f\n", t1->getMaterial().getShine(), t1->getMaterial().getRef());
// 	printf("Ref: %.2f, %.2f\n", h->getMaterial().getShine(), h->getMaterial().getRef());
	

// 	// rayTracer->addSphere(s3);

// 	return rayTracer;
// }

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
