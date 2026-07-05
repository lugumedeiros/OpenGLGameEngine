#include "../../../../include/engine/scene/camera/camBase.h"

BaseCamera::BaseCamera(float fov, float width, float heigth, float near, float far) {
	this->fov = ConfigValue<float>{ fov, 1.0f, 10.0f, 80.0f };
	projection = Projection{ fov, width, heigth, near, far};
}

// CONFIG

void BaseCamera::addRotation(glm::vec3 rotation) {
	rotationBuffer.add(rotation);
}

void BaseCamera::addTranslation(glm::vec3 translation) {
	movementBuffer.add(translation);
}

void BaseCamera::configSet(CAM_CONFIG config, float val, float inc, float min, float max) {
	ConfigValue<float>& cfg = getConfig(config);
	cfg = ConfigValue<float>{ val, inc, min, max };
}

void BaseCamera::configIncrement(CAM_CONFIG config) {
	ConfigValue<float>& cfg = getConfig(config);
	cfg.inc();
}

void BaseCamera::configDecrement(CAM_CONFIG config) {
	ConfigValue<float>& cfg = getConfig(config);
	cfg.dec();
}

void BaseCamera::configRestore(CAM_CONFIG config) {
	ConfigValue<float>& cfg = getConfig(config);
	cfg.restore();
}

void BaseCamera::lockTarget(bool isLocked) {
	isTargetLocked = isLocked;
	std::cout << "CAMERA TARGET LOCK SET TO: " << (isLocked ? "TRUE" : "FALSE") << std::endl;
}

// POSITION GETTER

void BaseCamera::printPosInfo() {
	std::cout << "POS:(" << pos.x << ", " << pos.y << ", " << pos.z << " )";
	std::cout << " - ROT:(" << getPitch() << ", " << getYaw() << ", " << getRoll() << ")" << std::endl;
	std::cout << "FRONT:(" << front.x << ", " << front.y << ", " << front.z << " )" << std::endl;
	std::cout << "UP:(" << up.x << ", " << up.y << ", " << up.z << " )" << std::endl;
	std::cout << "RIGHT:(" << right.x << ", " << right.y << ", " << right.z << " )" << std::endl;
	std::cout << "LOCK TARGET:(" << posLockTarget.x << ", " << posLockTarget.y << ", " << posLockTarget.z << " )" << std::endl;
	std::cout << "LOCKED: " << (isTargetLocked ? "TRUE" : "FALSE") << std::endl;
	std::cout << "VIEW: " << view[0][0] << " " << view[1][0] << " " << view[2][0] << " " << view[3][0] << '\n';
	std::cout << "FOV: " << fov.get() << std::endl;
	std::cout << "PROJECTION: " << projection.getMatrix()[0][0] << " " << projection.getMatrix()[1][1] << " " << projection.getMatrix()[2][2] << " " << projection.getMatrix()[3][3] << '\n';
	std::cout << "--------------------------------------------------" << std::endl;
}

float BaseCamera::getPitch() const {
	return glm::degrees(std::asin(glm::clamp(front.y, -1.0f, 1.0f)));
}

float BaseCamera::getYaw() const {
	return glm::degrees(std::atan2(front.x, -front.z));
}

float BaseCamera::getRoll() const {
	glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
	glm::vec3 rightNoRoll = glm::normalize(glm::cross(front, worldUp));
	if (glm::dot(rightNoRoll, rightNoRoll) < 1e-8f) {
		return 0.0f;
	}

	glm::vec3 upNoRoll = glm::cross(rightNoRoll, front);
	float angle = std::atan2(glm::dot(right, upNoRoll), glm::dot(up, upNoRoll));

	return glm::degrees(angle);
}

void BaseCamera::clearBuffers() {
	movementBuffer.clear();
	rotationBuffer.clear();
}

bool BaseCamera::isBufferEmpty() const {
	return movementBuffer.isZero() && rotationBuffer.isZero();
}

void BaseCamera::updateAxis() {
	up = orientation * glm::vec3(0.0f, 1.0f, 0.0f);
	right = orientation * glm::vec3(1.0f, 0.0f, 0.0f);
	front = orientation * glm::vec3(0.0f, 0.0f, -1.0f);
}

void BaseCamera::updateViewMatrix() {
	view = glm::lookAt(pos, pos + front, up);
}

ConfigValue<float>& BaseCamera::getConfig(CAM_CONFIG config) {
	switch (config) {
	case CAM_CONFIG::FOV:
		return fov;
	case CAM_CONFIG::MOV_SPEED:
		return movSpeed;
	case CAM_CONFIG::ROT_SPEED:
		return rotSpeed;
	default:
		throw std::invalid_argument("Invalid CAM_CONFIG enum value.");
	}
}
