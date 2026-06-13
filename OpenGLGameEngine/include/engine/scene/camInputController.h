#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../../include/engine/render/mesh.h"
#include "camera.h";

class CameraInputControl {
public:
	CameraInputControl(Camera& camera);
	void setCamera(Camera& camera);

	// INPUT CONTROLS
	void movXPositive(float press);
	void movYPositive(float press);
	void movZPositive(float press);

	void movXNegative(float press);
	void movYNegative(float press);
	void movZNegative(float press);

	void lock(float none) { cam.lockTarget(true); }
	void unlock(float none) { cam.lockTarget(false); }

	void setToWorld(float none) { cam.setIsWorldSpace(true); }
	void setToLocal(float none) { cam.setIsWorldSpace(false); }

	void incSpeed(float press);
	void decSpeed(float press);

	void toggleLock(float press);

private:
	Camera& cam;
	void mov(glm::vec3 dir);
};