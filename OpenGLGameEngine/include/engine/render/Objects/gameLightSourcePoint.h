#pragma once
#include "gameObjectBase.h"

class LightSource : public GameObjectBase {
public:
	LightSource(glm::vec3 color) : color(color) {};

	void setColor(glm::vec3 color) { this->color = color; }
	void setColor(float r, float g, float b) { this->color = glm::vec3(r, g, b); }
	void setDirection(glm::vec3 direction) { this->direction = glm::normalize(direction); }
	void setAttenuation(float linear, float quadratic) { this->linear = linear; this->quadratic = quadratic; }

	glm::vec3 getColor() const { return color; }
	glm::vec3 getDirection() const { return direction; }
	float getConstant() const { return constant; }
	float getLinear() const { return linear; }
	float getQuadratic() const { return quadratic; }

private:
	glm::vec3 color{ 1.0f };
	glm::vec3 direction{ 1.0f };  // TODO: update to orientation and pass to parentclass (maybe a class or something)
	float maxAngle{ 360.0f };

	float constant{ 1.0f }; // TODO: update to something easier like a range + intensity for easier use
	float linear{ 0.045f };
	float quadratic{ 0.0075f };
};