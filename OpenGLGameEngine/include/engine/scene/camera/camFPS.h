#pragma once
#include "camBase.h"

class FPSCamera : public BaseCamera {
public:
	using BaseCamera::BaseCamera;
	virtual void update(float deltaTime) override;
	virtual void setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll) override;

private:
	virtual void rotate(float delta) override;
	virtual void rotateToTarget(float delta, glm::vec3 target) override;
	virtual void movePos(float delta) override;

	float roll{ 0.0f };
	float minRoll{ -70.0f };
	float maxRoll{ 70.0f };

	float minPitch{ -70.0f };
	float maxPitch{ 70.0f };

	const glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
	const glm::vec3 worldRight{ 1.0f, 0.0f, 0.0f };
	const glm::vec3 worldFront{ 0.0f, 0.0f, -1.0f };
};