#include "../../include/render/material.h"

Material::Material(GLuint materialID, const Vector4& color, GLuint textureID, GLuint shaderProgramID):
	materialID(materialID),
	color( color ),
	textureID(textureID),
	shaderProgramID(shaderProgramID) {
}
