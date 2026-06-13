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

class InputHandler {
public:
	InputHandler() = default;
	void processInput(GLFWwindow* window);

	void setNewKey(int glfwKey, std::string_view keyName);
	void configKey(int glfwKey, bool shouldRepeat, int firstRepeatDelay, int repeatDelay);
	void setKeyPress(int glfwKey, std::function<void(float)> action);
	void setKeyRelease(int glfwKey, std::function<void(float)> action);

private:
	std::unordered_map<int, KeyBinding> keyMapping;
};