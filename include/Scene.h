#ifndef _SCENE_H_
#define _SCENE_H_
#include <vector>
#include <memory>


#include "Sphere.h"
#include "Material.h"
#include "Light.h"


class Scene {
private:

public:
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Light>> lights;

	Scene(void);
	~Scene();

    void addSphere(std::shared_ptr<Sphere> sphere);
	void addLight(std::shared_ptr<Light> light);

	void clear();
	
	int save(char * fileName);
	void load(char * fileName);

};

#endif