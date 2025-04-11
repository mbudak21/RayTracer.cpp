#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Ray.h"
#include "Material.h"

class Object {
    protected:
        Material mat;
    public:
        virtual ~Object() {};
        
        virtual bool hit(const Ray & r, HitRec & rec) const = 0;

        const Material& getMaterial() const;
    
        void setMaterial(const Material& m);
    };

#endif