#include "../../../include/engine/render/material.h"

void normalizeScale(float& f) {
	if (f > 1.0f) {
		f = 1.0f;
	}
	else if (f < 0.0f) {
		f = 0.0f;
	}
}

Material::Material(GLuint materialID, GLuint shaderProgramID):
	materialID(materialID),
	shaderProgramID(shaderProgramID) {
}

void Material::setColorOverlay(glm::vec4 color, float factor) {
	colorOverlay = color;
	colorOverlayFactor = factor;
	uniformChanged = true;
}

void Material::setBaseTexture(const Texture& texture, float factor) {
	textureBaseID = texture.ID;
	textureBaseFactor = factor;
	uniformChanged = true;
}

void Material::setOverlayTexture(const Texture& texture, float factor) {
	textureOverlayID = texture.ID;
	textureOverlayFactor = factor;
	uniformChanged = true;
}

void Material::normalize() {
	normalizeScale(colorOverlayFactor);
	normalizeScale(textureBaseFactor);
	normalizeScale(textureOverlayFactor);
}