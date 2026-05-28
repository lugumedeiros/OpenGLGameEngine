#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/window/window.h"
#include "../include/input/inputHandler.h"
#include "../include/render/render.h"

const int width = 800;
const int height = 600;
const char* title = "OpenGL Game Engine";

float verticesTriangle[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

int main() {
	MainWindow mainWindow(width, height, title);
	InputHandler inputHandler(&mainWindow);
	Render render(&mainWindow);

	GLFWwindow* window = mainWindow.getWindow();
	if (window == NULL) {
		return -1;
	}

	int success = render.setupRender(verticesTriangle, sizeof(verticesTriangle));
	if (!success) {
		return 1;
	}

	while (!mainWindow.shouldClose()) {
		inputHandler.processInput();
		
		// rendering start
		render.clear();
		render.render();

		// render end
		mainWindow.swapBuffers();
		mainWindow.pollEvents();
	}
	return 0;
}

