#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "keys.h"

class Engine;

struct KeyBinding {
	KeyObj key;
	std::function<void()> actionPress;
	std::function<void()> actionRelease;
};

class InputHandler {
public:
	InputHandler(Engine& engine);
	void processInput();

private:
	std::unordered_map<int, KeyBinding> keyMapping;
	Engine& engine;
	
	void setKeyPress();
	void setKeyRelease();

	///////////////////////////// MOVE TO ENGINE LATER ////////////////////////////////
	float speed = 0.2f;
	void toggleTestMode();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void toggleLockCam();
};