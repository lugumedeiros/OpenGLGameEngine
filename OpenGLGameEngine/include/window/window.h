#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* createMainWindow(int width, int height, const char* title);

class MainWindow {
public:
	MainWindow(int width, int height, const char* title);
	~MainWindow();

	GLFWwindow* getWindow();

	bool shouldClose();
	void pollEvents();
	void swapBuffers();
	void setClose();

private:
	GLFWwindow* window;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);