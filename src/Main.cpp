#include "RayTracer.h"
#include "Vec3.h" 
#include <iostream>

// TODO:
// Explain multi-threading in code.

RayTracer* initTracer(int width, int height) {
	RayTracer* rayTracer = new RayTracer(width, height);
	rayTracer->loadScene(SCENE);
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
