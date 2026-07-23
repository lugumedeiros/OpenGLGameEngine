#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shaderCompiler.h"
#include "textureService.h"
#include "map"


class Material {
public:
	Material(GLuint materialID, GLuint shaderProgramID);
	GLuint materialID{ 0 };
	GLuint shaderProgramID{ 0 };

	void setTint(glm::vec4 color, float factor);
	void setAlbedo(const Texture& albedoSample, float factor);
	void setSpecular(const Texture& specularSample);
	void setShininess(float value);

	const glm::vec4& getColorOverlay() { return colorTint; }
	float getColorOverlayFactor() const { return colorTintFactor; }
	GLuint getAlbedo() const { return albedoTextureID; }
	float getAlbedoFactor() const { return albedoTextureFactor; }
	GLuint getSpecular() const { return specularTextureID; }
	float getShininess() const { return shininess; }

	void normalizeFactor();

private:
	glm::vec4 colorTint{};
	float colorTintFactor{ 0.0f };

	GLuint albedoTextureID{ 0 };
	float albedoTextureFactor{ 0.0f };

	GLuint specularTextureID{ 0 };

	float shininess{ 32 };
};