#pragma once
#include "../../../include/engine/scene/camInputController.h"

CameraInputControl::CameraInputControl(Camera& camera) : cam(camera) {
}

void CameraInputControl::setCamera(Camera& camera) {
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

// CONFIG

void CameraInputControl::incSpeed(float press) {
	cam.incrementTranslateBufferSpeed(press);
}

void CameraInputControl::decSpeed(float press) {
	cam.incrementTranslateBufferSpeed(-press);
}

void CameraInputControl::toggleLock(float press){
	cam.lockTarget(!cam.getIsTargetLocked());
}

// INTERNAL

void CameraInputControl::rot(glm::vec3 rot) {
	cam.addRotationToBuffer(rot);
}

void CameraInputControl::mov(glm::vec3 dir) {
	cam.addTranslationToBuffer(dir);
}