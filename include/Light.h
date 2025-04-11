#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vec3.h"

class Light {
    public:
        Vec3f pos;
        Vec3f color;
        Light(Vec3f pos, Vec3f color);
        Light(Vec3f pos);// Use a default color

};

#endif