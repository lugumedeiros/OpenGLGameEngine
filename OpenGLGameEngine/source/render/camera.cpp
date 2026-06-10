#include "../../include/render/camera.h"
#include <iostream>

Camera::Camera(float fov, float width, float height, float near, float far) 
	: fov(fov), width(width), height(height), near(near), far(far) {
}

void Camera::setView(glm::mat4 mat4) {
	view = mat4;
}

void Camera::translateView(glm::vec3 vec3) {
	view = glm::translate(view, vec3);
	std::cout << "VIEW POS X:" << view[3][0] << " Y:" << view[3][1] << " Z:" << view[3][2] << std::endl;
}

void Camera::resetView() {
	view = glm::mat4(1.0f);
}

glm::mat4 Camera::getView() {
	return view;
}

glm::mat4 Camera::getProjection() {
	return glm::perspective(glm::radians(fov), width / height, near, far);
}

void Camera::setFOV(float fov) {
	this->fov = fov;
}

void Camera::setRes(float width, float height) {
	this->width = width;
	this->height = height;
}

void Camera::setNearFarPlanes(float near, float far) {
	this->near = near;
	this->far = far;
}
