#pragma once

#include <unordered_map>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../../window/window.h"
#include "shaderCompiler.h"

struct MeshVertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textureCoord;
	glm::vec3 normal;
};

class Mesh {
public:
	Mesh(GLuint meshID, GLuint indexCount, GLuint VAO, GLuint VBO, GLuint EBO) :
		meshID(meshID), indexCount(indexCount), VAO(VAO), VBO(VBO), EBO(EBO) {};

	GLuint meshID{0};
	GLuint indexCount{0};
	GLuint VAO{0};
	GLuint VBO{0};
	GLuint EBO{0};
};