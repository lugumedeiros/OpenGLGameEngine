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

	void setColorOverlay(glm::vec4 color, float factor);
	void setBaseTexture(const Texture& texture, float factor);
	void setOverlayTexture(const Texture& texture, float factor);
	void setSpecularFactor(float factor);
	void setShininess(float value);

	const glm::vec4& getColorOverlay() { return colorOverlay; }
	float getColorOverlayFactor() const { return colorOverlayFactor; }
	GLuint getTextureBaseID() const { return textureBaseID; }
	float getTextureBaseFactor() const { return textureBaseFactor; }
	GLuint getTextureOverlayID() const { return textureOverlayID; }
	float getTextureOverlayFactor() const { return textureOverlayFactor; }
	float getSpecularFactor() const { return specularFactor; }
	float getShininess() const { return shininess; }

	void normalize();
	bool uniformChanged{false};

private:
	glm::vec4 colorOverlay{};
	float colorOverlayFactor{ 0.0f };

	GLuint textureBaseID{ 0 };
	float textureBaseFactor{ 0.0f };

	GLuint textureOverlayID{ 0 };
	float textureOverlayFactor{ 0.0f };

	float specularFactor{ 0.5f };
	float shininess{ 32 };
};