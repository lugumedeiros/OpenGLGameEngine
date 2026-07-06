#include "../../../include/engine/camera/cam6DOF.h"

void Cam6DOF::update(float deltaTime) {
	if (isBufferEmpty() && deltaTime != 0.0f) { //deltaTime = 0 is always an internal call
		return;
	}
	movePos(deltaTime);
	if (isTargetLocked) {
		rotateToTarget(deltaTime, posLockTarget);
	} 	else {
		rotate(deltaTime);
	}
	updateAxis();
	updateViewMatrix();
	clearBuffers();
	printPosInfo();
}

void Cam6DOF::setView(glm::vec3 CamPos, glm::vec3 targetPos, float roll) {
	pos = CamPos;
	reset();
	rotateToTarget(0.0f, targetPos, roll);
	updateAxis();
	updateViewMatrix();
	printPosInfo();
}

void Cam6DOF::rotate(float delta) {
	glm::vec3 rot = rotationBuffer.get() * delta * rotSpeed.get();
	glm::quat qPitch = glm::angleAxis(glm::radians(rot.x), right);
	glm::quat qYaw = glm::angleAxis(glm::radians(-rot.y), up);
	glm::quat qRoll = glm::angleAxis(glm::radians(rot.z), front);
	orientation = glm::normalize(qYaw * qPitch * qRoll * orientation);
}

void Cam6DOF::rotateToTarget(float delta, glm::vec3 target) {
	float roll = rotationBuffer.get().z * delta * rotSpeed.get();
	rotateToTarget(delta, target, roll);
}

void Cam6DOF::rotateToTarget(float delta, glm::vec3 target, float roll) {
	glm::vec3 offset = target - pos;
	
	// lockpos and campos are equal
	if (glm::length(offset) < 1e-8f) {
		return;
	}
	
	glm::vec3 newFront = glm::normalize(offset);
	glm::vec3 refUp = worldUp;
	// newFront and Up are parallel
	if (glm::abs(glm::dot(newFront, refUp)) > 0.999f) {
		refUp = front;
	}

	glm::vec3 newRight = glm::normalize(glm::cross(newFront, refUp));
	glm::vec3 newUp = glm::cross(newRight, newFront);
	glm::quat rollQuat = glm::angleAxis(glm::radians(roll), newFront);

	orientation = glm::normalize(rollQuat * glm::quat_cast(glm::mat3{ newRight, newUp, -newFront }));
}

void Cam6DOF::movePos(float delta) {
	glm::vec3 input = movementBuffer.get() * delta * movSpeed.get();
	pos += right * input.x;
	pos += up * input.y;
	pos += front * input.z;
}

void Cam6DOF::lockTarget(bool isLocked) {
	isTargetLocked = isLocked;
	std::cout << "CAMERA TARGET LOCK SET TO: " << (isLocked ? "TRUE" : "FALSE") << std::endl;
	update(0.0f);
}

void Cam6DOF::reset() {
	orientation = glm::quat{ 1.0f, 0.0f, 0.0f, 0.0f };
	front = glm::vec3{ 0.0f, 0.0f, -1.0f };
	up = glm::vec3{ 0.0f, 1.0f, 0.0f };
	right = glm::vec3{ 1.0f, 0.0f, 0.0f };
}
