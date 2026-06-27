#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "keys.h"

struct KeyBinding {
	KeyObj key;
	std::function<void(float)> actionPress;
	std::function<void(float)> actionRelease;
};

enum InputDevice {
	DEVICE_KEYBOARD, DEVICE_MOUSE, DEVICE_JOYSTICK
};

class InputHandler {
public:
	InputHandler() = default;
	void processInput(GLFWwindow* window, double eventTime);

	void setNewKey(InputDevice device, int glfwKey, std::string_view keyName);
	void setNewKey(InputDevice device, int glfwKey, std::string_view keyName, bool shouldRepeat, double firstRepeatDelay, double repeatDelay, std::function<void(float)> pressAction, std::function<void(float)> releaseAction);
	void configKey(InputDevice device, int glfwKey, bool shouldRepeat, double firstRepeatDelay, double repeatDelay);
	void setKeyPress(InputDevice device, int glfwKey, std::function<void(float)> action);
	void setKeyRelease(InputDevice device, int glfwKey, std::function<void(float)> action);

	// MOUSE MOV
	void setMouseMovX(std::function<void(float)> action);
	void setMouseMovY(std::function<void(float)> action);

private:
	void processKeys(InputDevice device, GLFWwindow* window, double evenTime);

	std::unordered_map<int, KeyBinding> keyboardMapping;
	std::unordered_map<int, KeyBinding> mouseMapping;
	std::unordered_map<int, KeyBinding> joystickMapping;
	std::unordered_map<int, KeyBinding>& getMap(InputDevice device);

	int getKeyStatus(InputDevice device, GLFWwindow* window, int key);

	std::function<void(float)> movXAction{ nullptr };
	std::function<void(float)> movYAction{ nullptr };

	// MOUSE MOV
	double xMov{ 0.0 };
	double yMov{ 0.0 };
};