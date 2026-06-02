#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

class Vector4 {
public:
	Vector4(float x, float y, float z, float w);
	Vector4();
	float x;
	float y;
	float z;
	float w;
};

class ShaderProgram {
public:
	ShaderProgram(const char* vertexSource, const char* fragmentSource);
	void setVec4(std::string name, Vector4 vec);
	bool success{false};
	GLuint ID{ 0 };
	void loadUniformCache();

private:
	GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource);
	static bool compileShader(unsigned int* shader, int shaderType, const char* src);
	static bool linkProgramShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int FragmentShader);
	std::unordered_map<std::string, Vector4> uniformCache;
};
