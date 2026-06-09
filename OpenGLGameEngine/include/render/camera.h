#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera() = default;
	Camera(float fov, float widht, float height, float near, float far);

	void setView(glm::mat4 mat4);
	void translateView(glm::vec3 vec3);
	void resetView();
	glm::mat4 getView();

	glm::mat4 getProjection();

	void setFOV(float fov);
	void setRes(float width, float height);
	void setNearFarPlanes(float near, float far);

private:
	float fov{80.0f};
	float width{400.0f};
	float height{400.0f};
	float near{1.0f};
	float far{10.0f};

	glm::mat4 view{ glm::mat4(1.0f) };
};