#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Vec3.h"
#include "Color.h"
#include <cassert>

class Material {
    private:
        Color color;
    public:
        float shininess;
        float ref; // Reflectiveness
        float fuzz;
        float trnsp; // Transparency
    public:
        Material(); // We need to have a dafult constructor for HitRec, apperently (cpp shenenigans)
        Material(const Color& color, float shininess);
        Material(const Color& color, float shininess, float ref); // For manual reflectivity assignment

        //void setColor(const Color& color);

		const Vec3f& getAmbient() const;
		const Vec3f& getDiffuse() const;
		const Vec3f& getSpecular() const;
        const float getShine() const;
        const float getRef() const;
        const float getFuzz() const;
        const float getTrnsp() const;
    };

#endif