#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderCompiler.h"
#include "vectors.h"

class Material {
public:
	Material(GLuint materialID, const Vector4& color, GLuint textureID, GLuint shaderProgramID);
	GLuint materialID{0};
	Vector4 color{};
	GLuint textureID{0};
	GLuint shaderProgramID{0};
};