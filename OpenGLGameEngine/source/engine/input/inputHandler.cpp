#include "../../../include/engine/input/inputHandler.h"

void InputHandler::processInput(GLFWwindow* window) {
	static const float keyBoardPressure = 1.0f; // For now this only supports keyboard
	for (auto& [key, keyBinding] : keyMapping) {
		//const KeyObj& keyObj = keyBinding;
		int keyStatus = glfwGetKey(window, key);
		if (keyStatus == GLFW_PRESS) {
			if (keyBinding.key.press()) {
				if (keyBinding.actionPress != nullptr) {
					keyBinding.actionPress(keyBoardPressure);
				}
			}
		}
		if (keyStatus == GLFW_RELEASE) {
			if (keyBinding.key.release()) {
				if (keyBinding.actionRelease != nullptr) {
					keyBinding.actionRelease(keyBoardPressure);
				}
			}
		}
	}
}

void InputHandler::setNewKey(int glfwKey, std::string_view keyName) {
	keyMapping.try_emplace(glfwKey, KeyBinding{ KeyObj{keyName, glfwKey, true, 60, 5}, nullptr, nullptr });
}

void InputHandler::configKey(int glfwKey, bool shouldRepeat, int firstRepeatDelay, int repeatDelay) {
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