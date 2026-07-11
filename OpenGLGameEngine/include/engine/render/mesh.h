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
	Mesh(GLuint meshID, GLuint indexCount, GLuint VAO, GLuint VBO, GLuint EBO);
	GLuint meshID{0};
	GLuint indexCount{0};
	GLuint VAO{0};
	GLuint VBO{0};
	GLuint EBO{0};

	const glm::mat4 getTransform() const { return transform; }
	const glm::mat3 getNormalMatrix() const { return normalMatrix; }
	void setTransform(glm::mat4 transform);
	void resetTransform();
	void scale(glm::vec3 scale3);
	void translate(glm::vec3 pos3);

private:
	void updateNormalMatrix();
	glm::mat4 transform{ glm::mat4(1.0f) };
	glm::mat3 normalMatrix{ glm::mat3(1.0f) };
};