#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "projection.h"
#include "../../support/supportClasses.h"

enum class CAM_CONFIG {
	FOV, MOV_SPEED, ROT_SPEED, ZOOM,
};

enum class CAM_CONFIG_OP {
	RESTORE, INCREMENT, DECREMENT, SET, SET_INC,
};

class CamBase {
public:
	CamBase(float fov, float widht, float height, float near, float far);

	virtual void update(float deltaTime) = 0;
	virtual void setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll) = 0;

	virtual void addRotation(glm::vec3 rotation);
	virtual void addTranslation(glm::vec3 translation);

	// CONFIG
	virtual void config(CAM_CONFIG configuration, CAM_CONFIG_OP operation, float value1);
	virtual void lockTarget(bool isLocked);
	virtual void setLockTargetPos(glm::vec3 targetPos) { posLockTarget = targetPos; };

	// GETTERS
	virtual bool getIsTargetLocked() { return isTargetLocked; };
	virtual glm::mat4 getProjection() const { return projection.getMatrix(); }
	virtual glm::mat4 getView() const { return view; }
	float getConfigVal(CAM_CONFIG cfg);

protected:
	virtual void rotate(float delta) = 0;
	virtual void rotateToTarget(float delta, glm::vec3 target) = 0;
	virtual void movePos(float delta) = 0;

	Projection projection;
	glm::mat4 view{ 1.0f };
	ConfigValue<float> fov{ 45.0f, 1.0f, 10.0f, 80.0f };
	ConfigValue<float> zoom1{ 20.0f };
	ConfigValue<float> movSpeed{ 20.0f, 5.0f };
	ConfigValue<float> rotSpeed{ 100.0f, 10.0f };
	VectorChangeBuffer movementBuffer{}; // x = right, y = up, z = forward/backward
	VectorChangeBuffer rotationBuffer{}; // x = pitch, y = yaw, z = roll
	glm::vec3 pos{ 0.0f };
	glm::quat orientation{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 posLockTarget{ 0.0f };
	bool isTargetLocked{ false };

	glm::vec3 up{ 0.0f, 1.0f, 0.0f };
	glm::vec3 front{ 0.0f, 0.0f, -1.0f };
	glm::vec3 right{ 1.0f, 0.0f, 0.0f, };

	ConfigValue<float>& getConfig(CAM_CONFIG config);
	virtual void printPosInfo();
	virtual float getPitch() const;
	virtual float getYaw() const;
	virtual float getRoll() const;
	
	void configUpdate(CAM_CONFIG config);
	virtual bool isBufferEmpty() const;
	virtual void clearBuffers();
	virtual void updateAxis();
	virtual void updateViewMatrix();
};
