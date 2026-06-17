#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>

// TODO: CONVERT TO QUARTERION

class Camera {
public:
	Camera() = default;
	Camera(float fov, float widht, float height, float near, float far);

	// CONFIG
	void setFOV(float fov);
	void setRes(float width, float height);
	void setNearFarPlanes(float near, float far);

	// TRANSLATION
	void addTranslationToBuffer(glm::vec3 deltaPos);
	void setTranslateBufferSpeed(float speed) { inputBufferMovSpeed = speed; }
	void incrementTranslateBufferSpeed(float inc) { inputBufferMovSpeed += inc * inputBufferMovSpeed; }

	// ROTATION
	void addRotationToBuffer(glm::vec3 rotation);
	void setRotationBufferSpeed(float speed) { inputBufferRotSpeed = speed; }
	void incrementRotationBufferSpeed(float inc) { inputBufferRotSpeed += inc * inputBufferRotSpeedInc; }

	// VIEW
	const glm::mat4& getView();
	const glm::mat4& getProjection();
	void update(float deltaTime);
	void setView(glm::vec3 CamPos, glm::vec3 targetPos);

	// LOCK
	void setLockTargetPos(glm::vec3 targetPos) { lockTargetPos = targetPos; };
	void lockTarget(bool isLocked);
	bool getIsTargetLocked() { return isTargetLocked; };

private:
	//PROJECTION ADN SPACE
	float fov{45.0f};
	float width{800.0f};
	float height{600};
	float near{1.0f};
	float far{100.0f};
	glm::vec3 pos{ 0.0f };
	glm::mat4 projection{ 1.0f };

	void setProjection();

	glm::quat orientation{ 1.0f, 0.0f, 0.0f, 0.0f };

	//ROTATION
	float inputBufferRotSpeed{ 60.0f };
	float inputBufferRotSpeedInc{ 1.0f };
	glm::vec3 inputBufferRotation{ 0.0f };

	//TRANSLATION
	glm::vec3 front{0.0f, 0.0f, -1.0f};
	glm::vec3 right{1.0f, 0.0f, 0.0f,};
	glm::vec3 up{ 0.0f, 1.0f, 0.0f };
	float inputBufferMovSpeed{ 5.0f };
	float inputBufferMovSpeedInc{ 0.5f };
	glm::vec3 inputBufferTranslation{ 0.0f };

	// LOCK
	glm::mat4 view{};
	glm::vec3 lockTargetPos{ 0.0f, 0.0f, 0.0f };
	bool isTargetLocked{ false };
	
	// INTERNAL
	void clearBuffer();
	void updateAxis();
	void printPosInfo();
	void movePosCam(float deltaTime);
	void rotateCam(float deltaTime);
	void rotateToTarget(glm::vec3 targetPos);
	bool isBufferEmpty();
};