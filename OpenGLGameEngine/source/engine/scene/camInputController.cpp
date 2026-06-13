#pragma once
#include "../../../include/engine/scene/camInputController.h"

CameraInputControl::CameraInputControl(Camera& camera) : cam(camera) {
}

void CameraInputControl::setCamera(Camera& camera) {
	cam = camera;
}

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

void CameraInputControl::incSpeed(float press) {
	cam.addTranslateBufferSpeed(press);
}

void CameraInputControl::decSpeed(float press) {
	cam.addTranslateBufferSpeed(-press);
}

void CameraInputControl::toggleLock(float press){
	cam.lockTarget(!cam.getIsTargetLocked());
}

void CameraInputControl::mov(glm::vec3 dir) {
	cam.addTranslationToBuffer(dir);
}