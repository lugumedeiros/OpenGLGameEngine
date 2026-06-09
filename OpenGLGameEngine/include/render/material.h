#pragma once
#include <string>
#include <vector>

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

	const glm::vec4& getColorOverlay() { return colorOverlay; }
	float getColorOverlayFactor() { return colorOverlayFactor; }
	GLuint getTextureBaseID() { return textureBaseID; }
	float getTextureBaseFactor() { return textureBaseFactor; }
	GLuint getTextureOverlayID() { return textureOverlayID; }
	float getTextureOverlayFactor() { return textureOverlayFactor; }

	void normalize();
	bool uniformChanged{false};

private:
	glm::vec4 colorOverlay{};
	float colorOverlayFactor{ 0.0f };

	GLuint textureBaseID{ 0 };
	float textureBaseFactor{ 0.0f };

	GLuint textureOverlayID{ 0 };
	float textureOverlayFactor{ 0.0f };
};