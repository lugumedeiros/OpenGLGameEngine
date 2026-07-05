#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Projection {
public:
	Projection() = default;
	Projection(float fov, float width, float heigth, float near, float far)
		: fov(fov), width(width), heigth(heigth), near(near), far(far) {
		update();
	};

	void update() {
		projection = glm::perspective(glm::radians(fov), width / heigth, near, far);
	};

	// SETTER
	void setFOV(float fov) {
		this->fov = fov;
		update();
	}
	
	void setRes(float width, float height) {
		this->width = width;
		this->heigth = height;
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
	float getHeight() const { return heigth; }
	float getNear() const { return near; }
	float getFar() const { return far; }
	float getAspectRatio() const { return width / heigth; }
	const glm::mat4& getMatrix() const { return projection; }

private:
	float fov{ 45.0f };
	float width{ 800.0f };
	float heigth{ 600 };
	float near{ 1.0f };
	float far{ 100.0f };
	glm::mat4 projection{ 1.0f };
};
