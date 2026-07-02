#include "camBase.h"

BaseCamera::BaseCamera(float fov, float widht, float height, float near, float far) {
	fov = ConfigValue<float>{ fov, 1.0f, 10.0f, 80.0f };
	projection = Projection{ fov, widht, height, near, far};
}

// CONFIG

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

// POSITION GETTER

void BaseCamera::printPosInfo() {
	std::cout << "POS:(" << pos.x << ", " << pos.y << ", " << pos.z << " )";
	std::cout << " - ROT:(" << getPitch() << ", " << getYaw() << ", " << getRoll() << ")" << std::endl;
}

float BaseCamera::getPitch() const {
	return 0.0f;
}

float BaseCamera::getYaw() const {
	return 0.0f;
}

float BaseCamera::getRoll() const {
	return 0.0f;
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
