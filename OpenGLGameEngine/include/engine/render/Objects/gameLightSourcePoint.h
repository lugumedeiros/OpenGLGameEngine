#pragma once
#include "gameObjectBase.h"

class LightSource : public GameObjectBase {
public:
	LightSource(glm::vec3 color) : color(color) {};

	void setColor(glm::vec3 color) { this->color = color; }
	void setColor(float r, float g, float b) { this->color = glm::vec3(r, g, b); }
	glm::vec3 getColor() const { return color; }

	void setDirection(glm::vec3 direction) { this->direction = glm::normalize(direction); }
	glm::vec3 getDirection() { return direction; }

private:
	glm::vec3 color{ 1.0f };
	glm::vec3 direction{ 1.0f };  // TODO: update to orientation and pass to parentclass (maybe a class or something)
	float maxAngle{ 360.0f };
};