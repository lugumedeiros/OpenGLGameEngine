#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>

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
	ShaderProgram(const std::string& vertexSourcePath, const std::string& fragmentSourcePath);
	void setVec4(std::string name, Vector4 vec);
	void loadUniformCache();
	
	bool success{false};
	GLuint ID{ 0 };

private:
	std::string readShaderSource(const std::string& sourcePath);
	GLuint createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
	static bool compileShader(unsigned int* shader, int shaderType, const char* src);
	static bool linkProgramShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int FragmentShader);
	
	std::unordered_map<std::string, Vector4> uniformCache;
};
