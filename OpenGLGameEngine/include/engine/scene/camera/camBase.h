#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "projection.h"
#include "../../../support/supportClasses.h"

enum class CAM_CONFIG {
	FOV, MOV_SPEED, ROT_SPEED
};

class BaseCamera {
public:
	BaseCamera(float fov, float widht, float height, float near, float far);

	virtual void update(float deltaTime);
	virtual void setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll);

	// CONFIG
	void configSet(CAM_CONFIG config, float val, float inc, float min, float max);
	void configIncrement(CAM_CONFIG config);
	void configDecrement(CAM_CONFIG config);
	void configRestore(CAM_CONFIG config);

private:
	virtual void rotate(float delta);
	virtual void rotateToTarget(float delta);
	virtual void movePos(float delta);

	Projection projection;
	ConfigValue<float> fov{ 45.0f, 1.0f, 10.0f, 80.0f };
	ConfigValue<float> movSpeed{ 5.0f, 0.5f };
	ConfigValue<float> rotSpeed{ 60.0f, 1.0f };
	VectorChangeBuffer movementBuffer{};
	VectorChangeBuffer rotationBuffer{};
	glm::vec3 pos{ 0.0f };
	glm::quat orientation{ 1.0f, 0.0f, 0.0f, 0.0f };

	ConfigValue<float>& getConfig(CAM_CONFIG config);
	void printPosInfo();
	float getPitch() const;
	float getYaw() const;
	float getRoll() const;
};
