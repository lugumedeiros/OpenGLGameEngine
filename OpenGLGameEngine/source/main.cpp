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

unsigned int verticesLeft[] = {
	0, 4, 1,
};

unsigned int verticesRight[] = {
	4, 2, 3,
};

unsigned int verticesMiddle[] = {
	4, 3, 1,
};

std::string_view vertexPath = "source/shaders/vs_basic.glsl";
std::string_view fragmentColorPath = "source/shaders/fs_color.glsl";
std::string_view fragmentTexturePath = "source/shaders/fs_texture.glsl";
std::string_view fragmentUniformColorPath = "source/shaders/fs_uniform_color.glsl";
std::string_view fragmentColoredTexturePath = "source/shaders/fs_colored_texture.glsl";

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
	ShaderProgram* shaderProgram_color = engine.createShaderProgram( vertexPath, fragmentColorPath );
	if (shaderProgram_color == nullptr) {
		return 2;
	}

	ShaderProgram* shaderProgram_uniColor = engine.createShaderProgram( vertexPath, fragmentUniformColorPath );
	if (shaderProgram_uniColor == nullptr) {
		return 3;
	}

	ShaderProgram* shaderProgram_texture = engine.createShaderProgram( vertexPath, fragmentColoredTexturePath);
	if (shaderProgram_texture == nullptr) {
		return 4;
	}

	Mesh* meshIDLeft = engine.createMesh(verticesTriangle, sizeof(verticesTriangle), verticesLeft, sizeof(verticesLeft));
	Mesh* meshIDRight = engine.createMesh(verticesTriangle, sizeof(verticesTriangle), verticesRight, sizeof(verticesRight));
	Mesh* meshIDMiddle = engine.createMesh(verticesTriangle, sizeof(verticesTriangle), verticesMiddle, sizeof(verticesMiddle));

	Texture* textureWall = engine.getTexture("awesomeface");
	if (textureWall == nullptr) {
		return 5;
	}

	Vector4 colorBlack(1.0f, 1.0f, 1.0f, 1.0f);
	Material* materialIDColor = engine.createMaterial(colorBlack, textureWall->ID, shaderProgram_color);
	Material* materialIDTexture = engine.createMaterial(colorBlack, textureWall->ID, shaderProgram_texture);
	Material* materialIDUniColor = engine.createMaterial(colorBlack, textureWall->ID, shaderProgram_uniColor);
	
	UniqueColorChange effectColor(1.0f, 0.0f, 0.0f, 1.0f);
	engine.setUniformVec4(shaderProgram_uniColor, "uniformColor", Vector4(effectColor.r, effectColor.g, effectColor.b, 1.0f));

//////////////////////////////

	while (!mainWindow.shouldClose()) {
		engine.processInput();
		
		//effect update
		engine.setUniformVec4(shaderProgram_texture, "uniformColor", Vector4(effectColor.r, effectColor.g, effectColor.b, 1.0f));
		effectColor.advance();
		// rendering start

		engine.clearRender();
		engine.renderMesh(meshIDLeft, materialIDColor);
		engine.renderMesh(meshIDMiddle, materialIDTexture);
		engine.renderMesh(meshIDRight, materialIDUniColor);

		// render end
		mainWindow.swapBuffers();
		mainWindow.pollEvents();
	}
	return 0;
}

