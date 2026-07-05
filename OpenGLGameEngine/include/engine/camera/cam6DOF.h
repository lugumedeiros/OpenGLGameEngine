#pragma once
#include "camBase.h"

class Cam6DOF : public CamBase {
public:
	using CamBase::CamBase;
	void update(float deltaTime) override;
	void setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll) override;

private:
	void rotate(float delta) override;
	void rotateToTarget(float delta, glm::vec3 target) override;
	void movePos(float delta) override;
	void lockTarget(bool isLocked) override;
};