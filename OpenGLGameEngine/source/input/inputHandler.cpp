#include "../../include/input/inputHandler.h"

InputHandler::InputHandler(MainWindow* mainWindow) {
	window = mainWindow;
}

InputHandler::~InputHandler() {
}

void InputHandler::processInput() {
	if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "Window set to be closed." << std::endl;
		window->setClose();
	}
}
