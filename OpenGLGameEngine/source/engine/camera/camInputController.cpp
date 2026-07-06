#pragma once
#include "../../../include/engine/camera/camInputController.h"

CameraInputControl::CameraInputControl(CamBase& camera) : cam(camera) {
}

void CameraInputControl::setCamera(CamBase& camera) {
	cam = camera;
}

// MOVEMENT

void CameraInputControl::movXPositive(float intensity) {
	mov(glm::vec3{ intensity, 0.0f, 0.0f });
}

void CameraInputControl::movYPositive(float intensity) {
	mov(glm::vec3{ 0.0f, intensity, 0.0f });
}

void CameraInputControl::movZPositive(float intensity) {
	mov(glm::vec3{ 0.0f, 0.0f, intensity });
}

void CameraInputControl::movXNegative(float intensity) {
	mov(glm::vec3{ -intensity, 0.0f, 0.0f });
}

void CameraInputControl::movYNegative(float intensity) {
	mov(glm::vec3{ 0.0f, -intensity, 0.0f });
}

void CameraInputControl::movZNegative(float intensity) {
	mov(glm::vec3{ 0.0f, 0.0f, -intensity });
}

// ROTATION

void CameraInputControl::pitchPositive(float press) {
	rot(glm::vec3{ press, 0.0f, 0.0f });
}

void CameraInputControl::yawPositive(float press) {
	rot(glm::vec3{ 0.0f, press, 0.0f });
}

void CameraInputControl::rollPositive(float press) {
	rot(glm::vec3{ 0.0f, 0.0f, press });
}

void CameraInputControl::pitchNegative(float press) {
	rot(glm::vec3{ -press, 0.0f, 0.0f });
}

void CameraInputControl::yawNegative(float press) {
	rot(glm::vec3{ 0.0f, -press, 0.0f });
}

void CameraInputControl::rollNegative(float press) {
	rot(glm::vec3{ 0.0f, 0.0f, -press });
}

void CameraInputControl::pitch(float press) {
	rot(glm::vec3{ press * mouseSensitivity, 0.0f, 0.0f });
}

void CameraInputControl::yaw(float press) {
	rot(glm::vec3{ 0.0f, -press * mouseSensitivity, 0.0f });
}

// CONFIG

void CameraInputControl::toggleLock(float press){
	cam.lockTarget(!cam.getIsTargetLocked());
}

void CameraInputControl::toggleFPSMode(float press) {
	return;
	//TODO
}

// ZOOM
void CameraInputControl::zoom(float press) {
	CAM_CONFIG_OP op = (press <= 0.0f) ? CAM_CONFIG_OP::INCREMENT : CAM_CONFIG_OP::DECREMENT;
	cam.config(CAM_CONFIG::FOV, op, 0.0f);
}

void CameraInputControl::zoomIncrease(float press) {
	cam.config(CAM_CONFIG::FOV, CAM_CONFIG_OP::SET, 0.0f);
}

void CameraInputControl::zoomDecrease(float press) {
	cam.config(CAM_CONFIG::FOV, CAM_CONFIG_OP::DECREMENT, 0.0f);
}

void CameraInputControl::zoomSet(float press) {
	cam.config(CAM_CONFIG::FOV, CAM_CONFIG_OP::SET, cam.getConfigVal(CAM_CONFIG::ZOOM));
}

void CameraInputControl::zoomUnset(float press) {
	cam.config(CAM_CONFIG::FOV, CAM_CONFIG_OP::RESTORE, 0.0f);
}

// INTERNAL

void CameraInputControl::rot(glm::vec3 rot) {
	cam.addRotation(rot);
}

void CameraInputControl::mov(glm::vec3 dir) {
	cam.addTranslation(dir);
}