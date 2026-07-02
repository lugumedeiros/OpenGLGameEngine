#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Projection {
public:
	Projection(float fov, float widht, float height, float near, float far);

	void update() {
		projection = glm::perspective(glm::radians(fov), width / height, near, far);
	}

	// SETTER
	void setFOV(float fov) {
		this->fov = fov;
		update();
	}
	
	void setRes(float width, float height) {
		this->width = width;
		this->height = height;
		update();
	}
	
	void setNearFarPlanes(float near, float far) {
		this->near = near;
		this->far = far;
		update();
	}

	// GETTER
	float getFOV() const { return fov; }
	float getWidth() const { return width; }
	float getHeight() const { return height; }
	float getNear() const { return near; }
	float getFar() const { return far; }
	float getAspectRatio() const { return width / height; }
	const glm::mat4& getMatrix() const { return projection; }

private:
	float fov{ 45.0f };
	float width{ 800.0f };
	float height{ 600 };
	float near{ 1.0f };
	float far{ 100.0f };
	glm::mat4 projection{ 1.0f };
};
