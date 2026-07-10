#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>

static const std::vector<std::string> uniformNamesToLoad{
	"colorOverlayFactor",		// Blend Factor for Color Overlay Texture
	"baseTexFactor",			// Blend Factor for Base Texture
	"overlayTexFactor",			// Blen Factor for Overlay Texture
	"colorOverlay",				// Solid Color that blends with the gpu loaded mesh color
	"baseTexture",				// Texture sample 0
	"overlayTexture",			// Texture sample 1
	"ambientColor",				// Color of the ambient light hitting the mesh
	"ambientColorFactor",		// Blend Factor for the Ambient Light
	"sourceLightPos",			// Main Source Light Pos
	"sourceLightColor",			// Main Source Light Color
	"sourceLightFactor",		// Main Source Light Factor
	"uModel",					// Mesh Space -> World Space 
	"uView",					// World Space -> Camera Space
	"uProjection",				// Camera Space -> Projection Space
};

class ShaderProgram {
public:
	ShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath);
	
	int success{false};

	GLuint getID() const;
	GLint getUniformID(std::string_view uniform);

private:
	GLuint ID{ 0 };
	std::string readShaderSource(std::string_view sourcePath);
	GLuint createShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);
	GLuint compileShader(GLenum shaderType, std::string_view src);
	GLuint linkProgramShader(GLuint vertexShader, GLuint FragmentShader);
	
	std::map<std::string, GLint> uniformCache;
};
