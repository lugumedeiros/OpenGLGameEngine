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
	pitch += inputBufferRotation.x * inputBufferRotSpeed * deltaTime;
	yaw += inputBufferRotation.y * inputBufferRotSpeed * deltaTime;
	
	pitch = glm::clamp(pitch, -89.9f, 89.f);

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, glm::vec3{ 0.0f, 1.0f, 0.0f }));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::rotateToTarget() {
	glm::vec3 direction {glm::normalize(lockTargetPos - pos )};
	pitch = glm::degrees(asin((direction.y)));
	yaw = glm::degrees(atan2(direction.z, direction.x));
	
	front = direction;
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::update(float deltaTime) {
	if (isBufferEmpty() && deltaTime != 0.0f) { //deltaTime = 0 is always an internal call
		return;
	}
	movePosCam(deltaTime);
	if (isTargetLocked) {
		rotateToTarget();
	} else {
		rotateCam(deltaTime);
	}
	view = glm::lookAt(pos, pos + front, up);
	clearBuffer();
	std::cout << "POS: X:" << pos.x << " Y:" << pos.y << " Z:" << pos.z << " - ROT: Pitch:" << pitch << " Yaw:" << yaw << std::endl;
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