#pragma once
#include <unordered_map>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../window/window.h"
#include "shaderCompiler.h"
#include "mesh.h"

struct RenderObj {
	int RenderId;
	GLuint ProgramId;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	size_t verticesToDraw;
};

class Render {
public:
	Render(MainWindow*);
	~Render();
	bool isTest;

	void setClearColor(float r, float g, float b, float a);
	void clear();
	void setTest(bool isTest);

	void render(GLuint meshID, GLuint shaderProgramID);
	GLuint newMesh(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize);

private:
	MainWindow* window;

	std::unordered_map<int, Mesh> meshs;
	GLuint meshID{ 1 };
	GLuint createMeshObj(GLuint VAO, GLuint VBO, GLuint EBO, GLuint verticesToDraw);
};
