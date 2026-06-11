#include "../../include/render/camera.h"
#include <iostream>

Camera::Camera(float fov, float width, float height, float near, float far) 
	: fov(fov), width(width), height(height), near(near), far(far) {
	setProjection();
}

// Set view to target without rotation (default)
void Camera::setView(glm::vec3 cameraPos, glm::vec3 targetPos) {
	setView(cameraPos, targetPos, defaultCamUp);
}

// Set view to target with camera rotation
void Camera::setView(glm::vec3 cameraPos, glm::vec3 targetPos, glm::vec3 upDirection) {
	this->view = glm::lookAt(cameraPos, targetPos, upDirection);
}

// Set view directly
void Camera::setView(glm::mat4 view) {
	this->view = view;
}

// Translate camera into xyz direction 
void Camera::translateView(glm::vec3 vec3) {
	view = glm::translate(view, vec3);
	std::cout << "VIEW POS X:" << view[3][0] << " Y:" << view[3][1] << " Z:" << view[3][2] << std::endl;
}

void Camera::resetView() {
	view = defaultView;
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
