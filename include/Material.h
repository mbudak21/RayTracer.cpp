#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Vec3.h"

class Material {
    public:
        Vec3f color;
        float shininess;
        Vec3f specularColor;
    public:
        Material(Vec3f color); 
        Material(); // Use a default color

        void setColor(const Vec3f& vec);
		const Vec3f& getColor() const;
    };

#endif