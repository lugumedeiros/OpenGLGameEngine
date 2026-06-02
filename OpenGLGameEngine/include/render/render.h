#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../window/window.h"
#include "shaderCompiler.h"
#include "mesh.h"

class Render {
public:
	Render(MainWindow*);
	~Render();
	bool isTest;

	void setClearColor(float r, float g, float b, float a);
	void clear();
	void setTest(bool isTest);

	void render(GLuint meshID, ShaderProgram shaderProgram);
	GLuint newMesh(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize);

private:
	MainWindow* window;

	std::unordered_map<int, Mesh> meshs;
	GLuint meshID{ 1 };
	GLuint createMeshObj(GLuint VAO, GLuint VBO, GLuint EBO, GLuint verticesToDraw);
};
