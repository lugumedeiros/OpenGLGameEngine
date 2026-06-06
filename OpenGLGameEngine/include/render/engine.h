#pragma once
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../window/window.h"
#include "shaderCompiler.h"
#include "mesh.h"
#include "textureService.h"
#include "material.h"
#include "render.h"
#include "../input/inputHandler.h"

class Engine {
public:
	Engine(MainWindow* window);

	Mesh* createMesh(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize);
	ShaderProgram* createShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath);
	Material* createMaterial(const Vector4& color, GLuint textureID, ShaderProgram* shaderProgram);
	Texture* createTexture(std::string_view texturePath);
	Texture* getTexture(std::string_view textureName);

	void setUniformVec4(ShaderProgram*, std::string_view name, const Vector4& vec);

	void renderMesh(Mesh* mesh, Material* material);
	void clearRender();
	void setTest(bool isTest);

	void processInput();

private:
	InputHandler inputHandler;
	Render render;

	ShaderProgram* getShaderProgram(GLuint shaderProgramID);
	std::map<GLuint, ShaderProgram> shaderPrograms;
	
	Mesh* getMesh(GLuint meshID);
	std::map<GLuint, Mesh> meshs;
	GLuint meshID{ 1 };

	Material* getMaterial(GLuint materialID);
	std::map<GLuint, Material> materials;
	GLuint materialID{ 1 };

	const std::string textureDir{ R"(C:\C Desktop\Sandbox\Cpp\OpenGLGameEngine\OpenGLGameEngine\OpenGLGameEngine\assets\textures)" };
	TextureService textureService{};
};