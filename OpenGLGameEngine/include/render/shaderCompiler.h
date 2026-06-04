#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>
#include "vectors.h"

class ShaderProgram {
public:
	ShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath);
	void setUniformVec4(std::string_view name, const Vector4& vec);
	void loadUniformCache();
	
	bool success{false};

	GLuint getID() const;

private:
	GLuint ID{ 0 };
	std::string readShaderSource(std::string_view sourcePath);
	GLuint createShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);
	static bool compileShader(unsigned int* shader, int shaderType, std::string_view src);
	static bool linkProgramShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int FragmentShader);
	
	std::map<std::string, Vector4> uniformCache;
};
