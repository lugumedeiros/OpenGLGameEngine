#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "keys.h"
#include "../window/window.h"
#include "../render/render.h"


class InputHandler {
public:
	InputHandler(MainWindow* windowApp, Render* renderApp);
	~InputHandler();
	void processInput();

private:
	MainWindow* window;
	Render* render;

	// Keys - BAD FOR NOW
	KeyObj key_t{'t', GLFW_KEY_T, true, 60, 5};
};