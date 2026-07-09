#include "../../../include/engine/camera/camFPS.h"

void CamFPS::update(float deltaTime) {
	if (isBufferEmpty() && deltaTime != 0.0f) { //deltaTime = 0 is always an internal call
		return;
	}
	movePos(deltaTime);
	if (isTargetLocked) {
		rotateToTarget(deltaTime, posLockTarget);
	} else {
		updateRotation(deltaTime);
		rotate(deltaTime);
	}
	updateAxis();
	updateViewMatrix();
	clearBuffers();
	//printPosInfo();
}

void CamFPS::setView(glm::vec3 camPos, glm::vec3 targetPos, float roll) {
	this->roll = glm::clamp(roll, minRoll, maxRoll);
	pos = camPos;
	movePos(0.0f);
	rotateToTarget(0.0f, posLockTarget);
	updateAxis();
	updateViewMatrix();
	updateRotationFromAxis();
	printPosInfo();
}

void CamFPS::rotate(float delta) {
	glm::quat qPitch = glm::angleAxis(glm::radians(pitch), worldRight);
	glm::quat qYaw = glm::angleAxis(glm::radians(-yaw), worldUp);
	glm::quat qRoll = glm::angleAxis(glm::radians(roll), worldFront);
	orientation = glm::normalize(qYaw * qPitch * qRoll);
}


void CamFPS::rotateToTarget(float delta, glm::vec3 target) {
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

void CamFPS::movePos(float delta) {
	glm::vec3 input = movementBuffer.get();
	glm::vec3 horizontal = glm::normalize(glm::cross(front, worldUp));
	glm::vec3 depth = -glm::normalize(glm::cross(horizontal, worldUp));
	glm::vec3 movement = horizontal * input.x + worldUp * input.y + depth * input.z;
	pos += movement * delta * movSpeed.get();
}

void CamFPS::lockTarget(bool isLocked) {
	if (isTargetLocked && !isLocked) {
		updateRotationFromAxis();
	}
	isTargetLocked = isLocked;
	std::cout << "CAMERA TARGET LOCK SET TO: " << (isLocked ? "TRUE" : "FALSE") << std::endl;
	update(0.0f);
}

void CamFPS::updateRotation(float delta) {
	glm::vec3 rot = rotationBuffer.get() * delta * rotSpeed.get();

	float rollRad = glm::radians(roll);
	float c = cos(rollRad);
	float s = sin(rollRad);

	float pitchDelta = rot.x * c - rot.y * s;
	float yawDelta = rot.x * s + rot.y * c;

	pitch = glm::clamp(pitch + pitchDelta, minPitch, maxPitch);
	yaw = glm::mod(yaw + yawDelta, 360.0f);
	roll = glm::clamp(roll + rot.z, minRoll, maxRoll);
}

void CamFPS::updateRotationFromAxis() {
	yaw = getYaw();
	pitch = getPitch();
	roll = getRoll();
}