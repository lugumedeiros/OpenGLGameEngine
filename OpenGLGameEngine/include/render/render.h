#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../window/window.h"
#include "shader.h"

class Render {
public:
	Render(MainWindow*);
	~Render();

	void setClearColor(float r, float g, float b, float a);
	void clear();
	void setTest(bool isTest);
	void render();
	bool setupRender(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize);
	
	bool isTest;

private:
	ShaderCompiler compiler;
	MainWindow* window;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	size_t verticesToDraw;
};
