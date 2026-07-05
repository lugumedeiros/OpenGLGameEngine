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

	virtual void update(float deltaTime) = 0;
	virtual void setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll) = 0;

	void addRotation(glm::vec3 rotation);
	void addTranslation(glm::vec3 translation);

	// CONFIG
	void configSet(CAM_CONFIG config, float val, float inc, float min, float max);
	void configIncrement(CAM_CONFIG config);
	void configDecrement(CAM_CONFIG config);
	void configRestore(CAM_CONFIG config);
	void lockTarget(bool isLocked);
	void setLockTargetPos(glm::vec3 targetPos) { posLockTarget = targetPos; };

	// GETTERS
	bool getIsTargetLocked() { return isTargetLocked; };
	glm::mat4 getProjection() const { return projection.getMatrix(); }
	glm::mat4 getView() const { return view; }

protected:
	virtual void rotate(float delta) = 0;
	virtual void rotateToTarget(float delta, glm::vec3 target) = 0;
	virtual void movePos(float delta) = 0;

	Projection projection;
	glm::mat4 view{ 1.0f };
	ConfigValue<float> fov{ 45.0f, 1.0f, 10.0f, 80.0f };
	ConfigValue<float> movSpeed{ 20.0f, 5.0f };
	ConfigValue<float> rotSpeed{ 100.0f, 10.0f };
	VectorChangeBuffer movementBuffer{};
	VectorChangeBuffer rotationBuffer{};
	glm::vec3 pos{ 0.0f };
	glm::quat orientation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 posLockTarget{ 0.0f };
	bool isTargetLocked{ false };

	glm::vec3 up{ 0.0f, 1.0f, 0.0f };
	glm::vec3 front{ 0.0f, 0.0f, -1.0f };
	glm::vec3 right{ 1.0f, 0.0f, 0.0f, };

	ConfigValue<float>& getConfig(CAM_CONFIG config);
	void printPosInfo();
	float getPitch() const;
	float getYaw() const;
	float getRoll() const;
	
	bool isBufferEmpty() const;
	void clearBuffers();
	void updateAxis();
	void updateViewMatrix();
};
