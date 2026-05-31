#include "../../include/input/inputHandler.h"

InputHandler::InputHandler(MainWindow* window, Render* render) : window(window), render(render){
}

InputHandler::~InputHandler() {
}


void InputHandler::processInput() {
	if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "Window set to be closed." << std::endl;
		window->setClose();
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_T) == GLFW_PRESS) {
		if (key_t.press()) {
			render->setTest(!render->isTest);
			std::cout << "SET TEST: " << render->isTest << std::endl;
		}
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_T) == GLFW_RELEASE) {
		key_t.release();
	}
}


