#include "../../../include/engine/scene/camera.h"
#include <iostream>

Camera::Camera(float fov, float width, float height, float near, float far) 
	: fov(fov), width(width), height(height), near(near), far(far) {
	resetView();
	setProjection();
}

// Set view to target without rotation (default)
void Camera::setView(glm::vec3 cameraPos, glm::vec3 targetPos) {
	setView(cameraPos, targetPos, defaultUpDirection);
}

// Set view to target with camera rotation
void Camera::setView(glm::vec3 cameraPos, glm::vec3 targetPos, glm::vec3 upDirection) {
	this->cameraPos = cameraPos;
	this->targetPos = targetPos;
	this->upDirection = upDirection;
	update();
}

// Translate camera into xyz world direction, if tagetLocked then follow target
void Camera::translateWorldSpace(glm::vec3 deltaPos) {
	cameraPos += deltaPos;
	if (isTargetLocked) {
		targetPos = lockTargetPos;
	}
	else {
		targetPos += deltaPos;
	}
	update();
	std::cout << "VIEW POS X:" << cameraPos[0] << " Y:" << cameraPos[1] << " Z:" << cameraPos[2] << std::endl;
}

// Translate camere into xyz camera direction, if tagetLocked then follow target
void Camera::translateLocalSpace(glm::vec3 deltaPos) {
	glm::vec3 forward = glm::normalize(targetPos - cameraPos);
	glm::vec3 right = glm::normalize(glm::cross(forward, upDirection));
	glm::vec3 up = glm::normalize(glm::cross(right, forward));
	glm::vec3 refDelta{
		right * deltaPos.x
		+ up * deltaPos.y
		+ forward* deltaPos.z
	};
	translateWorldSpace(refDelta);
}

void Camera::resetView() {
	setView(defaultCameraPos, defaultTargetPos, defaultUpDirection);
}

const glm::mat4& Camera::getView() {
	return view;
}

const glm::mat4& Camera::getProjection() {
	return projection;
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

void Camera::setProjection() {
	projection = glm::perspective(glm::radians(fov), width / height, near, far);
}

void Camera::update() {
	this->view = glm::lookAt(cameraPos, targetPos, upDirection);
}

void Camera::lockTarget(bool isLocked) {
	isTargetLocked = isLocked; 
	std::cout << "CAMERA SET TO '" << (isLocked ? "TRUE" : "FALSE") << "'" << std::endl;
	translateWorldSpace(glm::vec3{ 0.0f });
}