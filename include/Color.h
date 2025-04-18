#ifndef _COLOR_H_
#define _COLOR_H_

#include "Vec3.h"
#include "cassert"

struct Color {
    Vec3f ambient;
    Vec3f diffuse;
    Vec3f specular;

    Color(const Vec3f& amb, const Vec3f& diff, const Vec3f& spec) {
        assertColor(amb);
        assertColor(diff);
        assertColor(spec);
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
    }

    inline const void assertColor(const Vec3f& c) {
        assert(1.0f >= c.x >= 0.0f && 1.0f >= c.y >= 0.0f && 1.0f >= c.z >= 0.0f);
    }
};

// class Color {
//     private:
//         Vec3f ambC; // ambient color
//         Vec3f diffC; // diffuse color
//         Vec3f specC; // specular color

//         inline const void assertColor(const Vec3f& c) {
//             assert(1.0f >= c.x >= 0.0f && 1.0f >= c.y >= 0.0f && 1.0f >= c.z >= 0.0f);
//         }


//     public:
//         Color();
//         Color(const Vec3f& ambientColor, const Vec3f& diffuseColor, const Vec3f& specularColor){
//             this->assertColor(ambientColor);
//             this->assertColor(diffuseColor);2
//             this->assertColor(specularColor);
//             this->ambC = ambientColor;
//             this->diffC = diffuseColor;
//             this->specC = specularColor;
//         }
//         const Vec3f& getAmbient(){
//             return this->ambC;
//         }
//         const Vec3f& getDiffuse(){
//             return this->diffC;
//         }
//         const Vec3f& getSpecular(){
//             return this->specC;
//         }
// };

#endif