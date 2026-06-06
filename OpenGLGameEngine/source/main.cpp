#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/window/window.h"
#include "../include/input/inputHandler.h"
#include "../include/render/engine.h"
#include "../include/effecs/uniqueColorChange.h"


const int width = 800;
const int height = 600;
const char* title = "OpenGL Game Engine";

float verticesTriangle[] = {
	// position				// color			// texture coords
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// 0 left down back
	-1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// 1 left up back
	1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 2 right down back
	1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,	// 3 right up back

	0.0f, -1.0f, -1.0f,		1.0f, 0.0f, 1.0f,	0.5f, 0.0f,	// 4 middle down back
	0.0f, 1.0f, -1.0f,		1.0f, 1.0f, 0.0f,	0.5f, 1.0f,	// 5 middle up back
	};

unsigned int verticesTriangleMiddle[] = {
	0, 2, 5,
};

//unsigned int verticesLeft[] = {
//	0, 4, 1,
//};
//
//unsigned int verticesRight[] = {
//	4, 2, 3,
//};
//
//unsigned int verticesMiddle[] = {
//	4, 3, 1,
//};

std::string_view vertexPath = "source/shaders/vs_basic.glsl";
std::string_view fragmentColorPath = "source/shaders/fs_complex.glsl";
//std::string_view fragmentTexturePath = "source/shaders/fs_texture.glsl";
//std::string_view fragmentUniformColorPath = "source/shaders/fs_uniform_color.glsl";
//std::string_view fragmentColoredTexturePath = "source/shaders/fs_colored_texture.glsl";

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

	Mesh* meshTriangle = engine.createMesh(verticesTriangle, sizeof(verticesTriangle), verticesTriangleMiddle, sizeof(verticesTriangleMiddle));

	Texture* textureBase = engine.getTexture("brickwall");
	if (textureBase == nullptr) {
		return 4;
	}

	Texture* textureOverlay = engine.getTexture("awesomeface");
	if (textureOverlay == nullptr) {
		return 3;
	}

	Vector4 colorOverlay(0.0f, 1.0f, 0.0f, 1.0f);
	float colorOverlayFactor = 1.0f;
	float baseTextureFactor = 1.0f;
	float ovelayTextureFactor = 1.0f;

	Material* materiaMainTriangle = engine.createMaterial(*shaderProgram_Texture);
	materiaMainTriangle->setColorOverlay(colorOverlay, colorOverlayFactor);
	materiaMainTriangle->setBaseTexture(*textureBase, baseTextureFactor);
	materiaMainTriangle->setOverlayTexture(*textureOverlay, ovelayTextureFactor);
	
	UniqueColorChange effectColor(1.0f, 0.0f, 0.0f, 1.0f);

//////////////////////////////

	while (!mainWindow.shouldClose()) {
		engine.processInput();
		
		//effect update
		effectColor.advance();
		materiaMainTriangle->setColorOverlay(Vector4{ effectColor.r, effectColor.g, effectColor.b, 1.0f }, colorOverlayFactor);
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
		engine.renderMesh(meshTriangle, materiaMainTriangle);

		// render end
		mainWindow.swapBuffers();
		mainWindow.pollEvents();
	}
	return 0;
}

