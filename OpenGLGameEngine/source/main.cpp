#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/window/window.h"
#include "../include/input/inputHandler.h"
#include "../include/render/render.h"
#include "../include/render/shaderCompiler.h"
#include "../include/effecs/uniqueColorChange.h"

const int width = 800;
const int height = 600;
const char* title = "OpenGL Game Engine";

float verticesTriangle[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,		// 0 left down back
	-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,		// 1 left up back
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		// 2 right down back
	0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,		// 3 right up back
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,		// 4 left down front
	-0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,		// 5 left up front
	0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,		// 6 right down front
	0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,			// 7 right up front
	};

unsigned int verticesLeft[] = {
	1, 0, 2,
	//2, 1, 3,
};

unsigned int verticesRight[] = {
	2, 1, 3,
};

const char* vertexPath = "source/shaders/basic_vert.glsl";
const char* fragmentPath = "source/shaders/basic_frag.glsl";

int main() {
	MainWindow mainWindow(width, height, title);
	Render render(&mainWindow);
	InputHandler inputHandler(&mainWindow, &render);

	GLFWwindow* window = mainWindow.getWindow();
	if (window == NULL) {
		return -1;
	}

////////////////// TEST AREA
	UniqueColorChange colorEffect1{ 0.0f, 0.0f, 0.0f, 1.0f };
	ShaderProgram shaderProgram_01 = ShaderProgram{ vertexPath, fragmentPath };
	if (!shaderProgram_01.success) {
		return 1;
	}

	UniqueColorChange colorEffect2{ 0.0f, 0.5f, 0.0f, 1.0f };
	ShaderProgram shaderProgram_02 = ShaderProgram{ vertexPath, fragmentPath };
	if (!shaderProgram_02.success) {
		return 1;
	}
	
	shaderProgram_01.setVec4("colorOut", Vector4{ colorEffect1.r, colorEffect1.g, colorEffect1.b, colorEffect1.a });
	shaderProgram_02.setVec4("colorOut", Vector4{ colorEffect2.r, colorEffect2.g, colorEffect2.b, colorEffect2.a });

	GLuint meshIDLeft = render.newMesh(verticesTriangle, sizeof(verticesTriangle), verticesLeft, sizeof(verticesLeft));
	GLuint meshIDRight = render.newMesh(verticesTriangle, sizeof(verticesTriangle), verticesRight, sizeof(verticesRight));
//////////////////////////////

	while (!mainWindow.shouldClose()) {
		inputHandler.processInput();
		
		// rendering start
		render.clear();
		
		shaderProgram_01.setVec4("colorOut", Vector4{ colorEffect1.r, colorEffect1.g, colorEffect1.b, colorEffect1.a });
		render.render(meshIDLeft, shaderProgram_01);
		colorEffect1.advance();

		shaderProgram_02.setVec4("colorOut", Vector4{ colorEffect2.r, colorEffect2.g, colorEffect2.b, colorEffect2.a });
		render.render(meshIDRight, shaderProgram_02);
		colorEffect2.advance();

		// render end
		mainWindow.swapBuffers();
		mainWindow.pollEvents();
	}
	return 0;
}

