#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "keys.h"
//#include "../render/engine.h"

class Engine;

enum class Action {
	MoveForward,
	MoveBackward,
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown,
	ToggleTestMode,
};

class InputHandler {
public:
	InputHandler(Engine& engine);
	~InputHandler();
	void processInput();

private:
	Engine& engine;
	
	void handleAction(Action action);

	std::unordered_map<int, KeyObj> keyMapping{
		{GLFW_KEY_T, KeyObj('t', GLFW_KEY_T, true, 60, 5)},
		{GLFW_KEY_W, KeyObj('w', GLFW_KEY_W, true, 20, 1)},
		{GLFW_KEY_A, KeyObj('a', GLFW_KEY_A, true, 20, 1)},
		{GLFW_KEY_S, KeyObj('s', GLFW_KEY_S, true, 20, 1)},
		{GLFW_KEY_D, KeyObj('d', GLFW_KEY_D, true, 20, 1)},
		{GLFW_KEY_LEFT_SHIFT, KeyObj(0, GLFW_KEY_D, true, 20, 1)},
		{GLFW_KEY_LEFT_CONTROL, KeyObj(0, GLFW_KEY_D, true, 20, 1)},
	};

	std::unordered_map<int, Action> releaseActions{
		//{GLFW_KEY_T, Action::ToggleTestMode},
		//{GLFW_KEY_W, Action::MoveForward},
		//{GLFW_KEY_S, Action::MoveBackward},
		//{GLFW_KEY_A, Action::MoveLeft},
		//{GLFW_KEY_D, Action::MoveRight}
	};

	std::unordered_map<int, Action > pressActions{
		{GLFW_KEY_T, Action::ToggleTestMode},
		{GLFW_KEY_W, Action::MoveForward},
		{GLFW_KEY_S, Action::MoveBackward},
		{GLFW_KEY_A, Action::MoveLeft},
		{GLFW_KEY_D, Action::MoveRight},
		{GLFW_KEY_LEFT_SHIFT, Action::MoveUp},
		{GLFW_KEY_LEFT_CONTROL, Action::MoveDown},
	};

	void toggleTestMode();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};