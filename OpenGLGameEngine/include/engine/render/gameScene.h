#pragma once

#include <vector>

#include "Objects/gameLightSourcePoint.h"
#include "Objects/gameObject.h"
#include "Objects/gameObjectBase.h"
#include "mesh.h"

class GameScene {
public:
	void addObject(GameObject& object) {
		objects.push_back(object);
	}

	void addLightSource(LightSourcePoint& light) {
		lightObjects.push_back(light);
	}

	void setAmbientSource(LightSourcePoint& ambientLight) {
		this->ambientLight = ambientLight;
	}

	std::vector<std::reference_wrapper<GameObject>> getObjects() { return objects; }
	std::vector<std::reference_wrapper<LightSourcePoint>> getLightObjects() { return lightObjects; }
	LightSourcePoint& getAmbientLight() { return ambientLight; }

private:

	std::vector<std::reference_wrapper<GameObject>> objects;
	std::vector<std::reference_wrapper<LightSourcePoint>> lightObjects;
	LightSourcePoint ambientLight{ glm::vec3{ 0.2f} };
};