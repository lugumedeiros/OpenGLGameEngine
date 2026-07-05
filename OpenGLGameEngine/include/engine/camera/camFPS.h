#pragma once
#include "camBase.h"

class CamFPS : public CamBase {
public:
	using CamBase::CamBase;
	void update(float deltaTime) override;
	void setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll) override;

private:
	void rotate(float delta) override;
	void rotateToTarget(float delta, glm::vec3 target) override;
	void movePos(float delta) override;
	void lockTarget(bool isLocked) override;

	float roll{ 0.0f };
	float minRoll{ -70.0f };
	float maxRoll{ 70.0f };

	float pitch{ 0.0f };
	float minPitch{ -70.0f };
	float maxPitch{ 70.0f };

	float yaw{ 0.0f };

	const glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
	const glm::vec3 worldRight{ 1.0f, 0.0f, 0.0f };
	const glm::vec3 worldFront{ 0.0f, 0.0f, -1.0f };

	void updateRotation(float delta);
	void updateRotationFromAxis();
};