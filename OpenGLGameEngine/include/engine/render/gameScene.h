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

	void setLightSource(LightSource light) {
		lightSource = light;
	}

	void setAmbientSource(LightSource ambientLight) {
		this->ambientLight = ambientLight;
	}

	void setDirectionalLight(LightSource directionalLight) {
		this->directionalLight = directionalLight;
	}

	std::vector<GameObject*>& getObjects() { return objects; }
	LightSource& getLightSource() { return lightSource; }
	LightSource& getAmbientLight() { return ambientLight; }
	LightSource& getDirectionalLight() { return directionalLight; }

private:
	std::vector<GameObject*> objects;
	LightSource lightSource{ glm::vec3{ 0.2f} };
	LightSource ambientLight{ glm::vec3{ 0.2f} };
	LightSource directionalLight{ glm::vec3{0.0f} };
};