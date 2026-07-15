#pragma once
#include "../mesh.h"
#include "../material.h"

class GameObjectBase {
public:
	const glm::mat4 getTransform() const { return transform; }
	
	const glm::mat3 getNormalMatrix() const { return normalMatrix; }
	
	void setTransform(glm::mat4 transform) {
		transform = transform;
		updateNormalMatrix();
	}
	
	void resetTransform() {
		transform = glm::mat4(1.0f);
		updateNormalMatrix();
	};
	
	void scale(glm::vec3 scale3) {
		transform = glm::scale(transform, scale3);
		updateNormalMatrix();
	};
	
	void translate(glm::vec3 pos3) {
		transform = glm::translate(transform, pos3);
		updateNormalMatrix();
	};

	glm::vec3 getPos() const {
		return glm::vec3{ transform[3][0], transform[3][1], transform[3][2] };
	}

private:
	void updateNormalMatrix() {
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(transform)));
	};

	glm::mat4 transform{ glm::mat4(1.0f) };
	glm::mat3 normalMatrix{ glm::mat3(1.0f) };
};
