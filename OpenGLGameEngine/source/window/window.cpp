#include "../../include/window/window.h"

MainWindow::MainWindow(int width, int height, const char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		window = NULL;
		return;
	}
	std::cout << "Window Created." << std::endl;
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

MainWindow::~MainWindow(){
	if (window != NULL) {
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

GLFWwindow* MainWindow::getWindow(){
	return window;
}

bool MainWindow::shouldClose(){
	return glfwWindowShouldClose(window);
}

void MainWindow::pollEvents(){
	glfwPollEvents();
}

void MainWindow::swapBuffers(){
	glfwSwapBuffers(window);
}

void MainWindow::setClose(){
	glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	std::cout << "DISPLAY CHANGED: " << width << " " << height << std::endl;
	glViewport(0, 0, width, height);
}
