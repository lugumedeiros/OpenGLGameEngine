#include "../../../include/engine/scene/camera.h"
#include "../../../include/support/supportFuncions.h"
#include <iostream>

Camera::Camera(float fov, float width, float height, float near, float far) 
	: fov(fov), width(width), height(height), near(near), far(far) {
	setProjection();
}

// MOVEMENT

void Camera::addTranslationToBuffer(glm::vec3 deltaPos) {
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

void Camera::setProjection() {
	projection = glm::perspective(glm::radians(fov), width / height, near, far);
}

void Camera::movePosCam(float deltaTime) {
	glm::vec3 movement{ 0.0f };
	movement += front * inputBufferTranslation.z;
	movement += right * inputBufferTranslation.x;
	movement += up * inputBufferTranslation.y;
	pos += movement * deltaTime * inputBufferMovSpeed;
}

void Camera::rotateCam(float deltaTime) {
	float pitchDelta = inputBufferRotation.x * inputBufferRotSpeed * deltaTime;
	float yawDelta = inputBufferRotation.y * inputBufferRotSpeed * deltaTime;
	float rollDelta = inputBufferRotation.z * inputBufferRotSpeed * deltaTime;

	glm::quat yawRotation = glm::angleAxis(glm::radians(-yawDelta), up);
	glm::quat pitchRotation = glm::angleAxis(glm::radians(pitchDelta), right);
	glm::quat rollRotation = glm::angleAxis(glm::radians(rollDelta), front);

	orientation = glm::normalize(yawRotation * pitchRotation * rollRotation * orientation);
}

void Camera::rotateToTarget(glm::vec3 target) {
	glm::vec3 offset{ target - pos };
	glm::vec3 direction {glm::normalize(offset)};
	
	// IF targetPOS == camPos
	if (glm::length(offset) < 1e-8f) {
		direction = front;
	}
	
	glm::vec3 forward(0.0f, 0.0f, -1.0f);
	float dot = glm::dot(forward, direction);
	
	// IF new orientation is the invers of current orientation
	if (dot < -0.99999f) {
		orientation = glm::angleAxis(glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
		return;
	}

	// IF new orientation is equal to current orientation}
	if (dot > 0.99999f) {
		orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		return;
	}

	glm::vec3 axis = glm::normalize(glm::cross(forward, direction));
	float angle = acos(glm::clamp(dot, -1.0f, 1.0f));
	orientation = glm::angleAxis(angle, glm::normalize(axis));
}

void Camera::update(float deltaTime) {
	if (isBufferEmpty() && deltaTime != 0.0f) { //deltaTime = 0 is always an internal call
		return;
	}
	movePosCam(deltaTime);
	if (isTargetLocked) {
		rotateToTarget(lockTargetPos);
	} else {
		rotateCam(deltaTime);
	}
	updateAxis();
	view = glm::lookAt(pos, pos + front, up);
	clearBuffer();
	printPosInfo();
}

void Camera::setView(glm::vec3 camPos, glm::vec3 lookPos) {
	pos = camPos;
	rotateToTarget(lookPos);
	updateAxis();
	view = glm::lookAt(pos, pos + front, up);
}

// CONFIG

void Camera::lockTarget(bool isLocked) {
	isTargetLocked = isLocked;
	std::cout << "CAMERA LOCK SET TO '" << (isLocked ? "TRUE" : "FALSE") << "'" << std::endl;
	update(0.0f);
}

void Camera::setFOV(float fov) {
	this->fov = fov;
	setProjection();
}

void Camera::setRes(float width, float height) {
	this->width = width;
	this->height = height;
	setProjection();
}

void Camera::setNearFarPlanes(float near, float far) {
	this->near = near;
	this->far = far;
	setProjection();
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
	float pitch{glm::degrees(asin(front.y))};
	float yaw{glm::degrees(atan2(front.x, -front.z))};
	float roll{0.0};

	std::cout << "POS:(" << pos.x << ", " << pos.y << ", " << pos.z << " )";
	std::cout << " - ROT:(" << pitch << ", " << yaw << ", " << roll << ")" << std::endl;
}