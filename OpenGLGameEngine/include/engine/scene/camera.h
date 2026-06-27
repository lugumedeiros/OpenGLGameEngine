#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../support/supportClasses.h"

class Camera {
public:
	Camera() = default;
	Camera(float fov, float widht, float height, float near, float far);

	// CONFIG
	void setFOV(float fov);
	void setRes(float width, float height);
	void setNearFarPlanes(float near, float far);
	void setFPSCamMode(bool enable);

	// TODO CREATE BUFFER CLASS
	// TRANSLATION
	void transBufferAddTranslation(glm::vec3 deltaPos);
	void transBufferSpeedSet(float speed) { inputBufferMovSpeed.set(speed); }
	void transBufferSpeedIncrement(float inc) { inputBufferMovSpeed.inc(inc); }

	// ROTATION
	void addRotationToBuffer(glm::vec3 rotation);
	void rotBufferSpeedSet(float speed) { inputBufferRotSpeed.set(speed); }
	void rotBufferSpeedIncrement(float inc) { inputBufferRotSpeed.inc(inc); }

	// FOV
	void fOVIncrement(bool isPos);
	void fOVSet() { fOVSet(zoomDefault); }
	void fOVSet(float val);
	void fOVRestore();
	float getFOV();
	void fOVSetLimit(float max, float min);

	// VIEW
	const glm::mat4& getView();
	const glm::mat4& getProjection();
	void update(float deltaTime);
	void setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll);

	// LOCK
	void setLockTargetPos(glm::vec3 targetPos) { lockTargetPos = targetPos; };
	void lockTarget(bool isLocked);

	// GETTERS
	bool getIsTargetLocked() { return isTargetLocked; };
	bool getFPSCamMode() { return isFPSCamMode; }

private:
	//PROJECTION AND SPACE
	ConfigValue<float> fov{45.0f, 1.0f, 10.0f, 80.0f};
	float zoomDefault = 20.0f;
	float width{800.0f};
	float height{600};
	float near{1.0f};
	float far{100.0f};
	glm::vec3 pos{ 0.0f };
	glm::mat4 projection{ 1.0f };

	void projectionUpdate();

	glm::quat orientation{ 1.0f, 0.0f, 0.0f, 0.0f };

	//ROTATION
	glm::vec3 inputBufferRotation{ 0.0f };
	ConfigValue<float> inputBufferRotSpeed{ 60.0f, 1.0f };
	bool isFPSCamMode{ false };

	glm::quat pitch{ 1,0,0,0 };
	glm::quat yaw{ 1,0,0,0 };
	glm::quat roll{ 1,0,0,0 };


	void rotateCamFree(float deltaTime);
	void rotateCamFPS(float delta);
	void rotateToTarget(float deltaTime, glm::vec3 targetPos);
	void rotateToTargetWithRoll(float deltaTime, glm::vec3 target, float roll);

	//TRANSLATION
	glm::vec3 front{0.0f, 0.0f, -1.0f};
	glm::vec3 right{1.0f, 0.0f, 0.0f,};
	glm::vec3 up{ 0.0f, 1.0f, 0.0f };
	glm::vec3 inputBufferTranslation{ 0.0f };
	ConfigValue<float> inputBufferMovSpeed{ 5.0f, 0.5f};

	// LOCK
	glm::mat4 view{};
	glm::vec3 lockTargetPos{ 0.0f, 0.0f, 0.0f };
	bool isTargetLocked{ false };
	
	// INTERNAL
	void clearBuffer();
	void updateAxis();
	void printPosInfo();
	float getPitch();
	float getYaw();
	float getRoll();
	void movePosCam(float deltaTime);
	void rollCamera(float roll);
	void rotate(float delta);
	bool isBufferEmpty();
};