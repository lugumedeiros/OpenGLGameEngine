#pragma once
#include "../window/window.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Render {
public:
	Render(MainWindow*);
	~Render();
	
	void SetClearColor(float r, float g, float b, float a);
	void clear();

private:
	MainWindow* window;
};