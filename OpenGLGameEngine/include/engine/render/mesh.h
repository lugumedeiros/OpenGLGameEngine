#pragma once

#include <unordered_map>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../../window/window.h"
#include "shaderCompiler.h"

class Mesh {
public:
	Mesh(GLuint meshID, GLuint indexCount, GLuint VAO, GLuint VBO, GLuint EBO);
	GLuint meshID{0};
	GLuint indexCount{0};
	GLuint VAO{0};
	GLuint VBO{0};
	GLuint EBO{0};

	const glm::mat4 getTransform() const { return transform; }
	void setTransform(glm::mat4 transform);
private:
	glm::mat4 transform{glm::mat4(1.0f)};
};