#pragma once
#include <glm/glm.hpp>

static glm::vec3 clampVec3Magnitude(glm::vec3 vec, float maxLen) {
	float len = glm::length(vec);
	if (len > maxLen) {
		return vec * (maxLen / len);
	}
	return vec;
}