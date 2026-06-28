#include "../../../include/engine/scene/camera.h"
#include "../../../include/support/supportFuncions.h"
#include <iostream>

Camera::Camera(float fov, float width, float height, float near, float far) 
	: width(width), height(height), near(near), far(far) {
	fov = ConfigValue{ fov, 1.0f, 0.0f, 90.0f };
	projectionUpdate();
}

// MOVEMENT

void Camera::transBufferAddTranslation(glm::vec3 deltaPos) {
	inputBufferTranslation += deltaPos;
}

// ROTATIONS

void Camera::addRotationToBuffer(glm::vec3 rotation) {
	inputBufferRotation += rotation;
}

// VIEW

const glm::mat4& Camera::getView() {
	return view;
}

const glm::mat4& Camera::getProjection() {
	return projection;
}

void Camera::projectionUpdate() {
	projection = glm::perspective(glm::radians(fov.get()), width / height, near, far);
}

void Camera::movePosCam(float deltaTime) {
	glm::vec3 movement{ 0.0f };
	movement += front * inputBufferTranslation.z;
	movement += right * inputBufferTranslation.x;
	movement += up * inputBufferTranslation.y;
	pos += movement * deltaTime * inputBufferMovSpeed.get();
}


void Camera::rotateCamFree(float deltaTime) {
	float pitchDelta = inputBufferRotation.x * inputBufferRotSpeed * deltaTime;
	float yawDelta = inputBufferRotation.y * inputBufferRotSpeed * deltaTime;
	float rollDelta = inputBufferRotation.z * inputBufferRotSpeed * deltaTime;

	glm::quat yawRotation = glm::angleAxis(glm::radians(-yawDelta), up);
	glm::quat pitchRotation = glm::angleAxis(glm::radians(pitchDelta), right);
	glm::quat rollRotation = glm::angleAxis(glm::radians(rollDelta), front);

	orientation = glm::normalize(yawRotation * pitchRotation * rollRotation * orientation);
}

void Camera::rotateCamFPS(float delta) {
	glm::quat pitchDelta = glm::angleAxis(glm::radians(inputBufferRotation.x * inputBufferRotSpeed * delta), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat yawDelta = glm::angleAxis(glm::radians(inputBufferRotation.y * inputBufferRotSpeed * -delta), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat rollDelta = glm::angleAxis(glm::radians(inputBufferRotation.z * inputBufferRotSpeed * delta), glm::vec3(0.0f, 0.0f, 1.0f));

	pitch *= pitchDelta;
	yaw *= yawDelta;
	roll *= rollDelta;

	orientation = glm::normalize(yaw * pitch * roll);
}

void Camera::rotateToTarget(float deltaTime, glm::vec3 target) {
	glm::vec3 offset = target - pos;
	glm::vec3 direction = glm::normalize(offset);
	if (glm::length(offset) < 0.001f) {
		direction = front;
	}

	glm::quat lookAtQuat = glm::quatLookAt(direction, up);
	float rollDelta = inputBufferRotation.z * inputBufferRotSpeed * deltaTime;
	glm::quat rollQuat = glm::angleAxis(glm::radians(rollDelta), direction);
	orientation = glm::normalize(rollQuat * lookAtQuat);
}

void Camera::rotateToTargetWithRoll(float deltaTime, glm::vec3 target, float roll) {
	glm::vec3 offset = target - pos;
	glm::vec3 direction;

	if (glm::length(offset) < 0.001f) {
		direction = front;
	}
	else {
		direction = glm::normalize(offset);
	}

	glm::quat rollQuat = glm::angleAxis(glm::radians(roll), direction);
	glm::vec3 rolledUp = glm::normalize(rollQuat * glm::vec3(0.0f, 1.0f, 0.0f));
	orientation = glm::normalize(glm::quatLookAt(direction, rolledUp));
}

void Camera::rollCamera(float roll) {
	glm::quat rollQuat = glm::angleAxis(glm::radians(roll), front);
	orientation = glm::normalize(rollQuat * orientation);
}

void Camera::rotate(float delta) {
	if (isTargetLocked) {
		rotateToTarget(delta, lockTargetPos);
		return;
	}
	if (isFPSCamMode) {
		rotateCamFPS(delta);
	} 
	else {
		rotateCamFree(delta);
	}
}

void Camera::update(float deltaTime) {
	if (isBufferEmpty() && deltaTime != 0.0f) { //deltaTime = 0 is always an internal call
		return;
	}
	if (isFPSCamMode && isTargetLocked) {
		isTargetLocked = false;
		std::cerr << "LOCKED AND FPS MODE IS UNVAILABLE FOR NOW..." << std::endl;
		return;
	}
	movePosCam(deltaTime);
	rotate(deltaTime);
	updateAxis();
	view = glm::lookAt(pos, pos + front, up);
	clearBuffer();
	printPosInfo();
}

void Camera::setView(glm::vec3 camPos, glm::vec3 lookPos, float roll) {
	pos = camPos;
	rotateToTargetWithRoll(0.0, lookPos, roll);
	updateAxis();
	view = glm::lookAt(pos, pos + front, up);
}

// CONFIG

void Camera::lockTarget(bool isLocked) {
	isTargetLocked = isLocked;
	std::cout << "CAMERA LOCK SET TO '" << (isLocked ? "TRUE" : "FALSE") << "'" << std::endl;
	update(0.0f);
}

void Camera::setFPSCamMode(bool enable) {
	// Conversion is not necessary from fps to free
	if (enable && !isFPSCamMode) {
		glm::vec3 euler = glm::eulerAngles(orientation);
		pitch = glm::angleAxis( euler.x, glm::vec3(1.0f, 0.0f, 0.0f) );
		yaw = glm::angleAxis( euler.y, glm::vec3(0.0f, 1.0f, 0.0f) );
		roll = glm::angleAxis( euler.z, glm::vec3(0.0f, 0.0f, 1.0f) );
		orientation = glm::normalize(roll * pitch * yaw); // the order is the inverse of what is used in FPS Cam
	}
	isFPSCamMode = enable;
	update(0.0f);
	std::cout << "CAMERA MODE SET TO '" << (enable ? "FPS" : "FREE") << std::endl;
}

void Camera::setRes(float width, float height) {
	this->width = width;
	this->height = height;
	projectionUpdate();
}

void Camera::setNearFarPlanes(float near, float far) {
	this->near = near;
	this->far = far;
	projectionUpdate();
}

// FOV
void Camera::fOVIncrement(bool isPos) {
	if (!isPos) {
		fov.inc();
	} else {
		fov.dec();
	}
	projectionUpdate();
}

void Camera::fOVSet(float val) {
	fov.set(val);
	projectionUpdate();
}

void Camera::fOVRestore() {
	fov.restore();
	projectionUpdate();
}

float Camera::getFOV() {
	return fov.get();
}

void Camera::fOVSetLimit(float max, float min){
	fov.setMinMax(min, max);
}

// INTERNAL

bool Camera::isBufferEmpty() {
	return inputBufferRotation == glm::vec3{ 0.0f } && inputBufferTranslation == glm::vec3{ 0.0f };
}

void Camera::clearBuffer() {
	inputBufferRotation = glm::vec3{ 0.0f };
	inputBufferTranslation = glm::vec3{ 0.0f };
}

void Camera::updateAxis() {
	front = glm::normalize(orientation * glm::vec3(0, 0, -1));
	right = glm::normalize(orientation * glm::vec3(1, 0, 0));
	up = glm::normalize(orientation * glm::vec3(0, 1, 0));
}

void Camera::printPosInfo() {
	std::cout << "POS:(" << pos.x << ", " << pos.y << ", " << pos.z << " )";
	std::cout << " - ROT:(" << getPitch() << ", " << getYaw() << ", " << getRoll() << ")" << std::endl;
}

float Camera::getPitch() {
	return glm::degrees(asin(front.y));
}

float Camera::getYaw() {
	return glm::degrees(atan2(front.x, -front.z));
}

float Camera::getRoll() {
	return glm::degrees(atan2(glm::dot(right, glm::vec3(0, 1, 0)), glm::dot(up, glm::vec3(0, 1, 0))));
}


