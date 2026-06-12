#include "../../include/input/inputHandler.h"
#include "../../include/render/engine.h"

InputHandler::InputHandler(Engine& engine) : engine(engine){

}

InputHandler::~InputHandler() {
}

void InputHandler::processInput() {
	GLFWwindow* window = engine.getWindow()->getWindow();
	for (auto& [key, obj] : keyMapping) {
		int keyStatus = glfwGetKey(window, key);
		
		if (keyStatus == GLFW_PRESS) {
			if (obj.press()) {
				auto it = pressActions.find(key);
				if (it != pressActions.end()) {
					handleAction(it->second);
				}
			}
		}
		if (keyStatus == GLFW_RELEASE) {
			if (obj.release()) {
				auto it = releaseActions.find(key);
				if (it != releaseActions.end()) {
					handleAction(it->second);
				}
			}
		}
	}
}

void InputHandler::handleAction(Action action) {
	switch (action) {
	case Action::MoveForward:
		moveForward();
		break;

	case Action::MoveBackward:
		moveBackward();
		break;

	case Action::MoveLeft:
		moveLeft();
		break;

	case Action::MoveRight:
		moveRight();
		break;

	case Action::MoveUp:
		moveUp();
		break;

	case Action::MoveDown:
		moveDown();
		break;

	case Action::ToggleTestMode:
		toggleTestMode();
		break;
	}
}

float speed = 0.02f;

void InputHandler::toggleTestMode() {
	Render* render = engine.getRender();
	bool isTest = render->isTest;
	render->setTest(!isTest);
}

void InputHandler::moveForward() {
	Camera* cam = engine.getCamera();
	cam->translate(glm::vec3(0.0f, 0.0f, speed));
}

void InputHandler::moveBackward() {
	Camera* cam = engine.getCamera();
	cam->translate(glm::vec3(0.0f, 0.0f, -speed));
}

void InputHandler::moveLeft() {
	Camera* cam = engine.getCamera();
	cam->translate(glm::vec3(speed, 0.0f, 0.0f));
}

void InputHandler::moveRight() {
	Camera* cam = engine.getCamera();
	cam->translate(glm::vec3(-speed, 0.0f, 0.0f));
}

void InputHandler::moveUp() {
	Camera* cam = engine.getCamera();
	cam->translate(glm::vec3(0.0f, -speed, 0.0f));
}

void InputHandler::moveDown() {
	Camera* cam = engine.getCamera();
	cam->translate(glm::vec3(0.0f, speed, 0.0f));
}


