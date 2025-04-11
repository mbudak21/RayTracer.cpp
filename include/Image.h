#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Vec3.h"

class Image { 
private:
	int width, height;
	Vec3f * pixels;

public:
	Image(const int w, const int h);
	~Image(void);
	int getWidth(void) const;
	int getHeight(void) const;
	void setPixel(const int x, const int y, const Vec3f & c);
	Vec3f getPixel(const int x, const int y);
	Vec3f * getPixelBufferPtr(void);
	void toPPM(const char* path);
	void toBMP(const char* path);
};

#endif