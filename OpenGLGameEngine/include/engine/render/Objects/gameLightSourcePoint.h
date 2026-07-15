#pragma once
#include "gameObjectBase.h"

class LightSourcePoint : public GameObjectBase {
public:
	LightSourcePoint(glm::vec3 color) : color(color) {};

	void set(glm::vec3 color) { this->color = color; }
	void set(float r, float g, float b) { this->color = glm::vec3(r, g, b); }
	glm::vec3 getColor() const { return color; }
	
private:
	glm::vec3 color{ 1.0f };
};