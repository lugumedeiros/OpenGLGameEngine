#pragma once
#include "../window/window.h"
#include "../../include/render/shader.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Render {
public:
	Render(MainWindow*);
	~Render();

	void SetClearColor(float r, float g, float b, float a);
	void clear();
	void render();
	bool setupRender(float* vertices, size_t verticesSize);

private:
	ShaderCompiler compiler;
	MainWindow* window;
	unsigned int VAO;
	unsigned int VBO;
};
