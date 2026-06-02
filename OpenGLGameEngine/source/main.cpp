#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/window/window.h"
#include "../include/input/inputHandler.h"
#include "../include/render/render.h"
#include "../include/render/shaderCompiler.h"

const int width = 800;
const int height = 600;
const char* title = "OpenGL Game Engine";

float verticesTriangle[] = {
	-0.5f, -0.5f, -0.5f,	// 0 left down back
	-0.5f, 0.5f, -0.5f,		// 1 left up back
	0.5f, -0.5f, -0.5f,		// 2 right down back
	0.5f, 0.5f, -0.5f,		// 3 right up back
	-0.5f, -0.5f, 0.5f,		// 4 left down front
	-0.5f, 0.5f, 0.5f,		// 5 left up front
	0.5f, -0.5f, 0.5f,		// 6 right down front
	0.5f, 0.5f, 0.5f,		// 7 right up front
	};

unsigned int verticesLeft[] = {
	1, 0, 2,
	//2, 1, 3,
};

unsigned int verticesRight[] = {
	2, 1, 3,
};

const char* getVertexShaderSource() {
	const char* vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec3 pos;\n"
		"void main(){\n"
		"gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);}\n\0";

	return vertexShader;
}

const char* getFragmentShaderSource() {
	const char* fragmentShader = "#version 330 core\n"
		"uniform vec4 colorOut;\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor = colorOut;}\n\0";
	return fragmentShader;
}


int main() {
	MainWindow mainWindow(width, height, title);
	Render render(&mainWindow);
	InputHandler inputHandler(&mainWindow, &render);

	GLFWwindow* window = mainWindow.getWindow();
	if (window == NULL) {
		return -1;
	}

////////////////// TEST AREA
	ShaderProgram shaderProgram_01 = ShaderProgram{ getVertexShaderSource(), getFragmentShaderSource() };
	if (!shaderProgram_01.success) {
		return 1;
	}


	ShaderProgram shaderProgram_02 = ShaderProgram{ getVertexShaderSource(), getFragmentShaderSource() };
	if (!shaderProgram_02.success) {
		return 1;
	}
	
	shaderProgram_01.setVec4("colorOut", Vector4{ 0.3f, 0.3f, 0.3f, 1.0f });
	shaderProgram_02.setVec4("colorOut", Vector4{ 0.0f, 0.3f, 0.7f, 1.0f });

	GLuint meshIDLeft = render.newMesh(verticesTriangle, sizeof(verticesTriangle), verticesLeft, sizeof(verticesLeft));
	GLuint meshIDRight = render.newMesh(verticesTriangle, sizeof(verticesTriangle), verticesRight, sizeof(verticesRight));
//////////////////////////////

	while (!mainWindow.shouldClose()) {
		inputHandler.processInput();
		
		// rendering start
		render.clear();
		render.render(meshIDLeft, shaderProgram_01);
		render.render(meshIDRight, shaderProgram_02);

		// render end
		mainWindow.swapBuffers();
		mainWindow.pollEvents();
	}
	return 0;
}

