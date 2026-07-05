#include "../../../../include/engine/scene/camera/camFPS.h"

void FPSCamera::update(float deltaTime) {
	if (isBufferEmpty() && deltaTime != 0.0f) { //deltaTime = 0 is always an internal call
		return;
	}
	movePos(deltaTime);
	if (isTargetLocked) {
		rotateToTarget(deltaTime, posLockTarget);
	} else {
		rotate(deltaTime);
	}
	updateAxis();
	updateViewMatrix();
	clearBuffers();
	printPosInfo();
}

void FPSCamera::setView(glm::vec3 camPos, glm::vec3 targetPos, float roll) {
	this->roll = roll;
	pos = camPos;
	movePos(0.0f);
	rotateToTarget(0.0f, posLockTarget);
	updateAxis();
	updateViewMatrix();
	printPosInfo();
}

void FPSCamera::rotate(float delta) {
	glm::vec3 rot = rotationBuffer.get() * delta * rotSpeed.get();
	roll = glm::clamp(roll + rot.z, minRoll, maxRoll);

	float pitchClamped = glm::clamp(getPitch() + rot.x, minPitch, maxPitch) - getPitch();

	glm::quat qYaw = glm::angleAxis(glm::radians(-rot.y), up);
	glm::quat qPitch = glm::angleAxis(glm::radians(pitchClamped), right);
	glm::quat qRoll = glm::angleAxis(glm::radians(rot.z), front);
	orientation = glm::normalize(qYaw * qPitch * qRoll * orientation);
	updateAxis();
}


void FPSCamera::rotateToTarget(float delta, glm::vec3 target) {
	roll = glm::clamp((rotationBuffer.get().z * delta * rotSpeed) + roll, minRoll, maxRoll);
	glm::vec3 offset = posLockTarget - pos;
	if (glm::length(offset) < 1e-8f) { // lockpos and campos are equal
		return;
	}
	glm::vec3 newFront = glm::normalize(offset);
	glm::vec3 newRight = glm::normalize(glm::cross(newFront, worldUp));
	glm::vec3 newUp = glm::cross(newRight, newFront);

	glm::mat3 rotation{ newRight, newUp, -newFront };
	glm::quat lookOrientation = glm::quat_cast(rotation);

	glm::quat rollQuat = glm::angleAxis(glm::radians(roll), newFront);
	orientation = glm::normalize(rollQuat * lookOrientation);
}

void FPSCamera::movePos(float delta) {
	glm::vec3 input = movementBuffer.get();

	glm::vec3 horizontal = glm::normalize(glm::cross(front, worldUp));
	glm::vec3 depth = -glm::normalize(glm::cross(horizontal, worldUp));

	glm::vec3 movement = horizontal * input.x + worldUp * input.y + depth * input.z;
	pos += movement * delta * movSpeed.get();
}