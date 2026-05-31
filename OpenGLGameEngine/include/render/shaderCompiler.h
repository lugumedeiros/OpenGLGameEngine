#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class ShaderCompiler {
public:
	GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource);
	bool success{false};
	GLuint programId{ 0 };

private:
	static bool compileShader(unsigned int* shader, int shaderType, const char* src);
	static bool linkProgramShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int FragmentShader);
};
