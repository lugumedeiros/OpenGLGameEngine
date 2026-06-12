#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera() = default;
	Camera(float fov, float widht, float height, float near, float far);

	void setView(glm::vec3 cameraPos, glm::vec3 targetPos);
	void setView(glm::vec3 cameraPos, glm::vec3 targetPos, glm::vec3 upDirection);

	void setFOV(float fov);
	void setRes(float width, float height);
	void setNearFarPlanes(float near, float far);

	void setLockTargetPos(glm::vec3 targetPos) { lockTargetPos = targetPos; };
	void lockTarget(bool isLocked);
	bool getIsTargetLocked() { return isTargetLocked; };

	void translate(glm::vec3 vec3);
	void resetView();
	
	const glm::mat4& getView();
	const glm::mat4& getProjection();

private:
	float fov{45.0f};
	float width{800.0f};
	float height{600};
	float near{1.0f};
	float far{100.0f};

	glm::vec3 defaultUpDirection{ 0.0f, 1.0f, 0.0f };
	glm::vec3 defaultCameraPos{ 0.0f, 0.0f, 10.0f };
	glm::vec3 defaultTargetPos{ 0.0f };

	glm::vec3 cameraPos{ defaultCameraPos };
	glm::vec3 targetPos { defaultTargetPos };
	glm::vec3 upDirection{ defaultUpDirection };

	glm::mat4 view{};
	glm::mat4 projection{ 1.0f };

	bool isTargetLocked{ false };
	glm::vec3 lockTargetPos{ 0.0f, 0.0f, 0.0f };

	void setProjection();
	void update();
};