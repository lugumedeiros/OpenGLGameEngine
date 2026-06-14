#pragma once
#include <map>
#include <string>
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../window/window.h"
#include "render/material.h"
#include "render/mesh.h"
#include "render/render.h"
#include "render/shaderCompiler.h"
#include "render/textureService.h"
#include "input/inputHandler.h"
#include "scene/camera.h"
#include "scene/camInputController.h"

class Engine {
public:
	Engine(MainWindow* window, Camera& cam);

	// ----------- RENDER -----------  //

	Mesh* createMesh(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize);
	ShaderProgram* createShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath);
	Material* createMaterial(const ShaderProgram& shaderProgram);
	Texture* createTexture(std::string_view texturePath);
	Texture* getTexture(std::string_view textureName);
	void setActiveCamera(Camera& camera);

	// ----------- INPUT -----------  //

	void processInput();
	void configKeyInput(int glfwKey, bool shouldRepeat, int firstRepeatDelay, int repeatDelay);
	void setKeyInputAction(int glfwKey, int glfwPressType, std::function<void(float)> action);
	void setDefaultKeyInputs();

	// ----------- CAMERA -----------  //

	void renderMesh(Mesh* mesh, Material* material);
	void clearRender();
	void setTest(bool isTest);

	//TODO: REnder and Camera pass as REF

	Camera* getCamera() { return &selectedCamera; }
	Render* getRender() { return &render; }

	// ----------- WINDOW -----------  //

	MainWindow* getWindow() { return window; }

private:

	// ----------- RENDER -----------  //

	Render render;
	void setUniforms(Mesh& mesh, Material& material, Camera& camera);

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

	// ----------- INPUT -----------  //

	InputHandler inputHandler;
	CameraInputControl camInputControl{ selectedCamera };
	void configKeyInput();
	void setKeyInputAction();

	// ----------- CAMERA -----------  //

	Camera& selectedCamera;

	// ----------- WINDOW -----------  //

	MainWindow* window;

	// ----------- INTERNAL -----------  //
	
	double lastFrameTime{ glfwGetTime() };
	double setLastFrameTime() {
		lastFrameTime = glfwGetTime();
		return lastFrameTime;
	}
	double getLastFrameTime() { return lastFrameTime; }
};