#pragma once

#include <vector>

#include "Objects/gameLightSourcePoint.h"
#include "Objects/gameObject.h"
#include "Objects/gameObjectBase.h"
#include "mesh.h"

class GameScene {
public:
	void addObject(GameObject* object) {
		objects.push_back(object);
	}

	void setLightSource(LightSourcePoint light) {
		lightSource = light;
	}

	void setAmbientSource(LightSourcePoint ambientLight) {
		this->ambientLight = ambientLight;
	}

	std::vector<GameObject*>& getObjects() { return objects; }
	LightSourcePoint& getLightSource() { return lightSource; }
	LightSourcePoint& getAmbientLight() { return ambientLight; }

private:

	std::vector<GameObject*> objects;
	LightSourcePoint lightSource{ glm::vec3{ 0.2f} };
	LightSourcePoint ambientLight{ glm::vec3{ 0.2f} };
};