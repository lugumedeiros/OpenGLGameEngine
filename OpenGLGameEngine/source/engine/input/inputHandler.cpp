#include "../../../include/engine/input/inputHandler.h"

void InputHandler::processInput(GLFWwindow* window, double eventTime) {
	
	// MOUSE
	double newXMov;
	double newYMov;
	glfwGetCursorPos(window, &newXMov, &newYMov);
	if (movXAction != nullptr) {
		movXAction(xMov - newXMov);
	}
	if (movYAction != nullptr) {
		movYAction(yMov - newYMov);
	}
	xMov = newXMov;
	yMov = newYMov;

	// KEYS
	static const float keyPressure = 1.0f; // For now this only supports keyboard
	for (auto& [key, keyBinding] : keyMapping) {
		int keyStatus = glfwGetKey(window, key);
		if (keyStatus == GLFW_PRESS) {
			if (keyBinding.key.press(eventTime)) {
				if (keyBinding.actionPress != nullptr) {
					keyBinding.actionPress(keyPressure);
				}
			}
		}
		if (keyStatus == GLFW_RELEASE) {
			if (keyBinding.key.release()) {
				if (keyBinding.actionRelease != nullptr) {
					keyBinding.actionRelease(keyPressure);
				}
			}
		}
	}
}

void InputHandler::setNewKey(int glfwKey, std::string_view keyName) {
	keyMapping.try_emplace(glfwKey, KeyBinding{ KeyObj{keyName, glfwKey, true, 60.0, 5.0}, nullptr, nullptr });
}

void InputHandler::setNewKey(int glfwKey, std::string_view keyName, bool shouldRepeat, double firstRepeatDelay, double repeatDelay, std::function<void(float)> pressAction, std::function<void(float)> releaseAction) {
	keyMapping.try_emplace(glfwKey, KeyBinding{ KeyObj{keyName, glfwKey, shouldRepeat, firstRepeatDelay, repeatDelay}, pressAction, releaseAction });
}

void InputHandler::configKey(int glfwKey, bool shouldRepeat, double firstRepeatDelay, double repeatDelay) {
	auto keyBind = keyMapping.find(glfwKey);
	if (keyBind != keyMapping.end()) {
		KeyObj& key = keyBind->second.key;
		key.setRepeat(shouldRepeat, firstRepeatDelay, repeatDelay);
	}
	std::cerr << "ERROR: GLFWKEY '" << glfwKey << "' NOT FOUND FOR CONFIGURATION" << std::endl;
}

void InputHandler::setKeyPress(int glfwKey, std::function<void(float)> action) {
	auto keyBind = keyMapping.find(glfwKey);
	if (keyBind != keyMapping.end()) {
		keyBind->second.actionPress = action;
	}
	std::cerr << "ERROR: GLFWKEY '" << glfwKey << "' NOT FOUND FOR PRESS CONFIGURATION" << std::endl;
}

void InputHandler::setKeyRelease(int glfwKey, std::function<void(float)> action) {
	auto keyBind = keyMapping.find(glfwKey);
	if (keyBind != keyMapping.end()) {
		keyBind->second.actionRelease = action;
	}
	std::cerr << "ERROR: GLFWKEY '" << glfwKey << "' NOT FOUND FOR RELEASE CONFIGURATION" << std::endl;
}

void InputHandler::setMouseMovY(std::function<void(float)> action) {
	 movYAction = action;
}

void InputHandler::setMouseMovX(std::function<void(float)> action) {
	movXAction = action;
}
