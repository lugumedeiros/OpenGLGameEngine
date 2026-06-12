#include "../../include/input/inputHandler.h"
#include "../../include/render/engine.h"

InputHandler::InputHandler(Engine& engine) : engine(engine){

	//REMOVE LATER
	keyMapping.emplace(GLFW_KEY_T,				KeyBinding{ KeyObj{"T", GLFW_KEY_T, true, 60, 5},		[this]() {toggleTestMode();}, nullptr });
	keyMapping.emplace(GLFW_KEY_W,				KeyBinding{ KeyObj{"W", GLFW_KEY_W, true, 20, 1},		[this]() {moveForward();}, nullptr });
	keyMapping.emplace(GLFW_KEY_A,				KeyBinding{ KeyObj{"A", GLFW_KEY_A, true, 20, 1},		[this]() {moveLeft();}, nullptr});
	keyMapping.emplace(GLFW_KEY_S,				KeyBinding{ KeyObj{"S", GLFW_KEY_S, true, 20, 1},		[this]() {moveBackward();}, nullptr});
	keyMapping.emplace(GLFW_KEY_D,				KeyBinding{ KeyObj{"D", GLFW_KEY_D, true, 20, 1},		[this]() {moveRight();}, nullptr});
	keyMapping.emplace(GLFW_KEY_LEFT_SHIFT,		KeyBinding{ KeyObj{"lshift", GLFW_KEY_D, true, 20, 1},	[this]() {moveUp();}, nullptr});
	keyMapping.emplace(GLFW_KEY_LEFT_CONTROL,	KeyBinding{ KeyObj{"lctrl", GLFW_KEY_D, true, 20, 1},	[this]() {moveDown();}, nullptr});
	keyMapping.emplace(GLFW_KEY_L,				KeyBinding{ KeyObj{"L", GLFW_KEY_L, true, 20, 1},		[this]() {toggleLockCam();}, nullptr});
}

void InputHandler::processInput() {
	GLFWwindow* window = engine.getWindow()->getWindow();
	for (auto& [key, keyBinding] : keyMapping) {
		//const KeyObj& keyObj = keyBinding;
		int keyStatus = glfwGetKey(window, key);
		if (keyStatus == GLFW_PRESS) {
			if (keyBinding.key.press()) {
				if (keyBinding.actionPress != nullptr) {
					keyBinding.actionPress();
				}
			}
		}
		if (keyStatus == GLFW_RELEASE) {
			if (keyBinding.key.release()) {
				if (keyBinding.actionRelease != nullptr) {
					keyBinding.actionRelease();
				}
			}
		}
	}
}

///////////////////////////// MOVE TO ENGINE LATER ////////////////////////////////
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

void InputHandler::toggleLockCam() {
	Camera* cam = engine.getCamera();
	cam->lockTarget(!cam->getIsTargetLocked());
}