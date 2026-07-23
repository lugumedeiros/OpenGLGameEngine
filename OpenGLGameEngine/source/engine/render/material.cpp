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

void Material::setTint(glm::vec4 color, float factor) {
	colorTint = color;
	colorTintFactor = factor;
}

void Material::setAlbedo(const Texture& texture, float factor) {
	albedoTextureID = texture.ID;
	albedoTextureFactor = factor;
}

void Material::setSpecular(const Texture& specularSample) {
	specularTextureID = specularSample.ID;
}

void Material::setShininess(float value) {
	shininess = value;
}

void Material::normalizeFactor() {
	normalizeScale(colorTintFactor);
	normalizeScale(albedoTextureFactor);
}