#pragma once
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/window/window.h"
#include "../include/input/inputHandler.h"
#include "../include/render/engine.h"
#include "../include/effecs/uniqueColorChange.h"
#include "../include/render/camera.h"


const int width = 800;
const int height = 600;
const char* title = "OpenGL Game Engine";

float verticesTriangle[] = {
	// position				// color			// texture coords
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// 0 left down back
	-1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// 1 left up back
	1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 2 right down back
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,	// 3 right up back

	-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// 4 left down front
	-1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// 5 left up front
	1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 6 right down front
	1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,	// 7 right up front
	};

unsigned int verticesTriangleMiddle[] = {
	0, 2, 1, 1, 2, 3,
	4, 5, 6, 5, 7, 6,
	0, 1, 4, 1, 5, 4,
	2, 6, 3, 3, 6, 7,
	1, 3, 5, 3, 7, 5,
	0, 4, 2, 2, 4, 6
};

std::string_view vertexPath = "source/shaders/vs_basic.glsl";
std::string_view fragmentColorPath = "source/shaders/fs_complex.glsl";

std::string_view textureWallPath = "assets/textures/woodcontainer.jpg";
std::string_view textureSmilePath = "assets/textures/awesomeface.png";

int main() {
	MainWindow mainWindow(width, height, title);
	Engine engine(&mainWindow);

	GLFWwindow* window = mainWindow.getWindow();
	if (window == NULL) {
		return 1;
	}

	////////////////// TEST AREA
	ShaderProgram* shaderProgram_Texture = engine.createShaderProgram( vertexPath, fragmentColorPath );
	if (shaderProgram_Texture == nullptr) {
		return 2;
	}

	// MULTIPLE CUBES
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::mat4 model = glm::mat4(1.0f); // Model POS base
	std::vector<Mesh*> cubes{};
	for (auto pos : cubePositions) {
		Mesh* mesh = engine.createMesh(verticesTriangle, sizeof(verticesTriangle), verticesTriangleMiddle, sizeof(verticesTriangleMiddle));
		cubes.push_back(mesh);
		glm::mat4 translation = glm::translate(model, pos);
		translation = glm::scale(translation, glm::vec3(0.5, 0.5, 0.5));
		mesh->setTransform(translation);
	}

	// TEXTURE
	Texture* textureBase = engine.getTexture("brickwall");
	if (textureBase == nullptr) {
		return 4;
	}

	Texture* textureOverlay = engine.getTexture("awesomeface");
	if (textureOverlay == nullptr) {
		return 3;
	}

	glm::vec4 colorOverlay(0.0f, 1.0f, 0.0f, 1.0f);
	float colorOverlayFactor = 1.0f;
	float baseTextureFactor = 1.0f;
	float ovelayTextureFactor = 1.0f;

	Material* materiaMainTriangle = engine.createMaterial(*shaderProgram_Texture);
	materiaMainTriangle->setColorOverlay(colorOverlay, colorOverlayFactor);
	materiaMainTriangle->setBaseTexture(*textureBase, baseTextureFactor);
	materiaMainTriangle->setOverlayTexture(*textureOverlay, ovelayTextureFactor);
	
	UniqueColorChange effectColor(1.0f, 0.0f, 0.0f, 1.0f);

	// VIEW
	Camera cam{45.0f, float(width), float(height), 0.1f, 100.0f};
	engine.setActiveCamera(&cam);

	glm::mat4 projection = cam.getProjection();

///////////////// END TEST AREA

	while (!mainWindow.shouldClose()) {
		engine.processInput();
		
		//effect update
		effectColor.advance();
		materiaMainTriangle->setColorOverlay(glm::vec4( effectColor.r, effectColor.g, effectColor.b, 1.0f ), colorOverlayFactor);
		materiaMainTriangle->setBaseTexture(*textureBase, baseTextureFactor);
		materiaMainTriangle->setOverlayTexture(*textureOverlay, ovelayTextureFactor);
		if (colorOverlayFactor < 1.0f) {
			colorOverlayFactor += 0.004f;
		}
		else if (baseTextureFactor < 1.0f) {
			baseTextureFactor += 0.003f;
		}
		else if (ovelayTextureFactor < 1.0f) {
			ovelayTextureFactor += 0.003f;
		}
		else {
			colorOverlayFactor = 0.0f;
			baseTextureFactor = 0.0f;
			ovelayTextureFactor = 0.0f;
		}
		
		// rendering start
		engine.clearRender();

		// Render all cubes
		for (auto& cube : cubes) {
			engine.renderMesh(cube, materiaMainTriangle);
		}

		// render end
		mainWindow.swapBuffers();
		mainWindow.pollEvents();
	}
	return 0;
}

