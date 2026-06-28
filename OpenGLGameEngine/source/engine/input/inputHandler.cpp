#include "../../../include/engine/input/inputHandler.h"

void InputHandler::processKeys(InputDevice device, GLFWwindow* window, double eventTime) {
	float keyPressure = 1.0f; // For now this only supports clicks
	std::unordered_map<int, KeyBinding>& mapping = getMap(device);
	for (auto& [key, keyBinding] : mapping) {
		int keyStatus = getKeyStatus(device, window, key);
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

void InputHandler::processMouseMovement(GLFWwindow* window, double evenTime) {
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
}

void InputHandler::processMouseScroll(GLFWwindow* window, double evenTime) {
	if (mouseScrollDelta != 0.0f) {
		float normalized = mouseScrollDelta >= 0.0f ? 1.0f : -1.0f;
		mouseScrollAction(static_cast<float>(normalized));
		mouseScrollDelta = 0.0f;
	}
}

void InputHandler::processInput(GLFWwindow* window, double eventTime) {
	
	processMouseMovement(window, eventTime);
	processKeys(DEVICE_MOUSE, window, eventTime);
	processKeys(DEVICE_KEYBOARD, window, eventTime);
	processMouseScroll(window, eventTime);
	//process(DEVICE_JOYSTICK, window, eventTime);
}

void InputHandler::setNewKey(InputDevice device, int glfwKey, std::string_view keyName) {
	std::unordered_map<int, KeyBinding>& mapping = getMap(device);
	mapping.try_emplace(glfwKey, KeyBinding{ KeyObj{keyName, glfwKey, true, 60.0, 5.0}, nullptr, nullptr });
}

void InputHandler::setNewKey(InputDevice device, int glfwKey, std::string_view keyName, bool shouldRepeat, double firstRepeatDelay, double repeatDelay, std::function<void(float)> pressAction, std::function<void(float)> releaseAction) {
	std::unordered_map<int, KeyBinding>& mapping = getMap(device);
	mapping.try_emplace(glfwKey, KeyBinding{ KeyObj{keyName, glfwKey, shouldRepeat, firstRepeatDelay, repeatDelay}, pressAction, releaseAction });
}

void InputHandler::configKey(InputDevice device, int glfwKey, bool shouldRepeat, double firstRepeatDelay, double repeatDelay) {
	std::unordered_map<int, KeyBinding>& mapping = getMap(device);
	auto keyBind = mapping.find(glfwKey);
	if (keyBind != mapping.end()) {
		KeyObj& key = keyBind->second.key;
		key.setRepeat(shouldRepeat, firstRepeatDelay, repeatDelay);
		return;
	}
	std::cerr << "ERROR: GLFWKEY '" << glfwKey << "' NOT FOUND FOR CONFIGURATION" << std::endl;
}

void InputHandler::setKeyPress(InputDevice device, int glfwKey, std::function<void(float)> action) {
	std::unordered_map<int, KeyBinding>& mapping = getMap(device);
	auto keyBind = mapping.find(glfwKey);
	if (keyBind != mapping.end()) {
		keyBind->second.actionPress = action;
		return;
	}
	std::cerr << "ERROR: GLFWKEY '" << glfwKey << "' NOT FOUND FOR PRESS CONFIGURATION" << std::endl;
}

void InputHandler::setKeyRelease(InputDevice device, int glfwKey, std::function<void(float)> action) {
	std::unordered_map<int, KeyBinding>& mapping = getMap(device);
	auto keyBind = mapping.find(glfwKey);
	if (keyBind != mapping.end()) {
		keyBind->second.actionRelease = action;
		return;
	}
	std::cerr << "ERROR: GLFWKEY '" << glfwKey << "' NOT FOUND FOR RELEASE CONFIGURATION" << std::endl;
}

void InputHandler::setMouseMovY(std::function<void(float)> action) {
	 movYAction = action;
}

void InputHandler::setMouseMovX(std::function<void(float)> action) {
	movXAction = action;
}

void InputHandler::setScrollAction(GLFWwindow* window, std::function<void(float)> action) {
	glfwSetWindowUserPointer(window, this);
	glfwSetScrollCallback(window, mouseScrollCallback);
	mouseScrollAction = action;
}

std::unordered_map<int, KeyBinding>& InputHandler::getMap(InputDevice device) {
	switch (device) {
	case DEVICE_KEYBOARD:
		return keyboardMapping;

	case DEVICE_MOUSE:
		return mouseMapping;

	case DEVICE_JOYSTICK:
		return joystickMapping;
	
	default:
		throw("INVALID INPUT DEVICE.\n");
	}
}

int InputHandler::getKeyStatus(InputDevice device, GLFWwindow* window, int key) {
	switch (device)	{
	case DEVICE_KEYBOARD:
		return glfwGetKey(window, key);

	case DEVICE_MOUSE:
		return glfwGetMouseButton(window, key);

	case DEVICE_JOYSTICK:
		throw("JOYSTICK NOT IMPLEMENTED YET.\n");

	default:
		throw("INVALID INPUT DEVICE.\n");
	}
}

void InputHandler::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	if (auto* inputHandler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window))) {
		inputHandler->mouseScrollDelta += yOffset;
	}
}
