#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Vec3.h"

class Material {
    public:
        Vec3f color;
        float shininess;
        Vec3f specularColor;
        float ref; // Reflectiveness
    public:
        Material(); // We need to have a dafult constructor for HitRec 
        Material(Vec3f color);
        Material(Vec3f color, float shininess, Vec3f specularColor, float ref); 

        void setColor(const Vec3f& vec);
		const Vec3f& getColor() const;
    };

#endif