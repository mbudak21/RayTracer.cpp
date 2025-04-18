#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vec3.h"
#include "Color.h"

class Light {
    public:
        Color color;
        Vec3f pos;
    public:
        Light(Vec3f pos, Color color);
        //Light(Vec3f pos);// Use a default, all white color
		const Vec3f& getAmbient() const;
		const Vec3f& getDiffuse() const;
		const Vec3f& getSpecular() const;
};

#endif