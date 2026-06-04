#pragma once

#include <unordered_map>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../window/window.h"
#include "shaderCompiler.h"

class Mesh {
public:
	Mesh(GLuint meshID, GLuint indexCount, GLuint VAO, GLuint VBO, GLuint EBO);
	GLuint meshID;
	GLuint indexCount;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};