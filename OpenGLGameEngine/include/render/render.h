#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../window/window.h"
#include "shaderCompiler.h"
#include "mesh.h"
#include "textureService.h"
#include "material.h"

class Render {
public:
	Render(MainWindow*);
	~Render();

	void setClearColor(float r, float g, float b, float a);
	void clear();
	void setTest(bool isTest);
	void render(const Mesh& mesh, Material& material, ShaderProgram& shaderProgram);

	bool isTest{ false };
private:
	MainWindow* window;
};
