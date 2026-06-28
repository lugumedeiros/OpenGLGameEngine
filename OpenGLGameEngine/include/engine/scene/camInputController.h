#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h";
#include "../../../include/engine/render/mesh.h"

class CameraInputControl {
public:
	CameraInputControl(Camera& camera);
	void setCamera(Camera& camera);

	// CAM INPUT CONTROLS
	
	void movXPositive(float press);
	void movYPositive(float press);
	void movZPositive(float press);

	void movXNegative(float press);
	void movYNegative(float press);
	void movZNegative(float press);

	void pitchPositive(float press);
	void yawPositive(float press);
	void rollPositive(float press);

	void pitchNegative(float press);
	void yawNegative(float press);
	void rollNegative(float press);

	void pitch(float press);
	void yaw(float press);
	
	// CAM CONFIG CONTROLS

	void lock(float none) { cam.lockTarget(true); }
	void unlock(float none) { cam.lockTarget(false); }

	void incSpeed(float press);
	void decSpeed(float press);

	void toggleLock(float press);
	void toggleFPSMode(float press);


	// ZOOM
	void zoom(float press);
	void zoomIncrease(float press);
	void zoomDecrease(float press);
	void zoomSet(float press);
	void zoomUnset(float press);

private:
	Camera& cam;
	double mouseSensitivity{ 0.1f };
	void rot(glm::vec3 rot);
	void mov(glm::vec3 dir);
};