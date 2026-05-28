#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class ShaderCompiler {
public:
	//ShaderCompiler();
	//~ShaderCompiler();

	bool compileShader(unsigned int* shader, int shaderType, const char* src);
	bool linkProgramShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int FragmentShader);
	bool createShaderProgram(unsigned int* shaderProgram, const char* vertexSource, const char* fragmentSource);
};