#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../window/window.h"


class InputHandler {
public:
	InputHandler(MainWindow* mainWindow);
	~InputHandler();
	void processInput();

private:
	MainWindow* window;
};