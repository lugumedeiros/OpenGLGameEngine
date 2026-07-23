#pragma once
#include <iostream>
#include <vector>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/window/window.h"
#include "../include/engine/input/inputHandler.h"
#include "../include/engine/engine.h"
#include "../include/effecs/uniqueColorChange.h"
#include "../include/engine/camera/camFPS.h"
#include "../include/engine/camera/cam6DOF.h"
#include "../include/engine/render//Objects/gameLightSourcePoint.h"
#include "../include/engine/render//Objects/gameObject.h"
#include "../include/engine/render/gameScene.h"

// test
#include <thread>
#include <chrono>

const int width = 800;
const int height = 600;
const char* title = "OpenGL Game Engine";

const glm::vec3 leftNormal{ -1, 0, 0 };
const glm::vec3 rightNormal{ 1, 0, 0 };
const glm::vec3 topNormal{ 0, 1, 0 };
const glm::vec3 downNormal{ 0, -1, 0 };
const glm::vec3 backNormal{ 0, 0, -1 };
const glm::vec3 frontNormal{ 0, 0, 1 };

std::vector<MeshVertex> verticesTriangle = {
	// FACE LEFT
	MeshVertex{ glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), leftNormal},
	MeshVertex{ glm::vec3(-1.0f, +1.0f, -1.0f),	glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), leftNormal},
	MeshVertex{ glm::vec3(-1.0f, -1.0f, +1.0f),	glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), leftNormal},
	MeshVertex{ glm::vec3(-1.0f, +1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), leftNormal},

	// FACE RIGHT
	MeshVertex{ glm::vec3(+1.0f, -1.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), rightNormal},
	MeshVertex{ glm::vec3(+1.0f, +1.0f, -1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), rightNormal},
	MeshVertex{ glm::vec3(+1.0f, -1.0f, +1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), rightNormal},
	MeshVertex{ glm::vec3(+1.0f, +1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), rightNormal},

	// FACE TOP
	MeshVertex{ glm::vec3(-1.0f, +1.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), topNormal},
	MeshVertex{ glm::vec3(-1.0f, +1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), topNormal},
	MeshVertex{ glm::vec3(+1.0f, +1.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), topNormal},
	MeshVertex{ glm::vec3(+1.0f, +1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), topNormal},

	// FACE DOWN
	MeshVertex{ glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), downNormal},
	MeshVertex{ glm::vec3(-1.0f, -1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), downNormal},
	MeshVertex{ glm::vec3(+1.0f, -1.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), downNormal},
	MeshVertex{ glm::vec3(+1.0f, -1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), downNormal},

	// FACE BACK
	MeshVertex{ glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), backNormal},
	MeshVertex{ glm::vec3(-1.0f, +1.0f, -1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), backNormal},
	MeshVertex{ glm::vec3(+1.0f, -1.0f, -1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), backNormal},
	MeshVertex{ glm::vec3(+1.0f, +1.0f, -1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), backNormal},

	// FACE FRONT
	MeshVertex{ glm::vec3(-1.0f, -1.0f, +1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), frontNormal},
	MeshVertex{ glm::vec3(-1.0f, +1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), frontNormal},
	MeshVertex{ glm::vec3(+1.0f, -1.0f, +1.0f),	glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), frontNormal},
	MeshVertex{ glm::vec3(+1.0f, +1.0f, +1.0f),	glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), frontNormal},
};

unsigned int verticesTriangleMiddle[] = {
	// LEFT
	0,  2,  1,
	1,  2,  3,

	// RIGHT
	4,  6,  5,
	5,  6,  7,

	// TOP
	8, 10,  9,
	9, 10, 11,

	// BOTTOM
	12, 14, 13,
	13, 14, 15,

	// BACK (-Z)
	16, 18, 17,
	17, 18, 19,

	// FRONT (+Z)
	20, 22, 21,
	21, 22, 23,
};

std::string_view vertexPath = "source/shaders/vs_basic.glsl";
std::string_view fragmentColorPath = "source/shaders/fs_complex.glsl";
std::string_view fragmentLightPath = "source/shaders/fs_lightsource.glsl";

std::string_view textureWallPath = "assets/textures/woodcontainer.jpg";
std::string_view textureSmilePath = "assets/textures/awesomeface.png";

int main() {
	MainWindow mainWindow(width, height, title);
	//Cam6DOF cam{ 45.0f, float(width), float(height), 0.1f, 100.0f };
	CamFPS cam{ 45.0f, float(width), float(height), 0.1f, 100.0f };
	Engine engine(&mainWindow, cam);
	//engine.setActiveCamera(cam);

	GLFWwindow* window = mainWindow.getWindow();
	if (window == NULL) {
		return 1;
	}

	// TEXTURE
	Texture* textureBase = engine.getTexture("container2");
	if (textureBase == nullptr) {
		return 3;
	}

	Texture* textureOverlay = engine.getTexture("awesomeface");
	if (textureOverlay == nullptr) {
		return 3;
	}

	Texture* whiteMask = engine.getTexture("container2_specMask");
	if (whiteMask == nullptr) {
		return 3;
	}

	GameScene gameScene{};
	ShaderProgram* shaderProgram_Texture = engine.createShaderProgram( vertexPath, fragmentColorPath );
	if (shaderProgram_Texture == nullptr) {
		return 20;
	}
	ShaderProgram* shaderProgram_LightSource = engine.createShaderProgram(vertexPath, fragmentLightPath);
	if (shaderProgram_LightSource == nullptr) {
		return 21;
	}

	Material* materialMainTriangle = engine.createMaterial(*shaderProgram_Texture);
	materialMainTriangle->setTint(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f);
	materialMainTriangle->setShininess(32.0f);
	materialMainTriangle->setSpecular(*whiteMask);
	materialMainTriangle->setAlbedo(*textureBase, 1.0f);

	Material* materialLightSource = engine.createMaterial(*shaderProgram_LightSource);
	
	Mesh* cubeMesh = engine.createMesh(verticesTriangle, verticesTriangleMiddle, sizeof(verticesTriangleMiddle));

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

	// CUBES
	std::vector<GameObject> cubes;
	for (auto pos : cubePositions) {
		GameObject cube{ *cubeMesh, *materialMainTriangle };
		cube.translate(pos);
		cube.scale(glm::vec3(0.5, 0.5, 0.5));
		cubes.emplace_back(cube);
	}

	for (GameObject& cube : cubes) {
		gameScene.addObject(&cube);
	}

	// LIGHT SOURCE+CUBE
	glm::vec3 color{ 1.0f, 1.0f, 0.1f };
	materialLightSource->setTint(glm::vec4(color, 1.0f), 1.0f);
	GameObject lightSourceCube{ *cubeMesh, *materialLightSource };
	lightSourceCube.translate(glm::vec3(10.0f, 10.0f, -20.0f));
	lightSourceCube.scale(glm::vec3(0.5f));;
	gameScene.addObject(&lightSourceCube);

	LightSourcePoint& lightSource = gameScene.getLightSource();
	lightSource.set( color.x, color.y, color.z );
	lightSource.translate(glm::vec3(10.0f, 10.0f, -20.0f));
	lightSource.scale(glm::vec3(0.5f));

	glm::vec4 colorOverlay(0.0f, 1.0f, 0.0f, 1.0f);
	float colorOverlayFactor = 1.0f;
	float baseTextureFactor = 1.0f;
	float ovelayTextureFactor = 1.0f;
	
	UniqueColorChange effectColor(1.0f, 0.0f, 0.0f, 1.0f);

	// VIEW
	engine.setActiveCamera(cam);
	cam.setLockTargetPos(glm::vec3{ 0.0f, 0.0f, 0.0f });
	
	engine.processInput();
	cam.setView(glm::vec3{ 0.0f, 0.0f, 10.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, 0.0f);
	engine.renderGameScene(gameScene);

///////////////// END TEST AREA
	
	auto elapsed = std::chrono::microseconds(0);
	int pc = 1;

	while (!mainWindow.shouldClose()) {
		engine.processInput();

		//effect update
		effectColor.advance();
		float lightMov = pc > 300 ? 0.2f : -0.2f;

		//materialLightSource->setTint(glm::vec4(effectColor.r, effectColor.g, effectColor.b, 1.0f), 1.0f);
		//lightSource.set(effectColor.r, effectColor.g, effectColor.b);
		lightSourceCube.translate(glm::vec3(lightMov, 0.0f, 0.0f));
		lightSource.translate(glm::vec3(lightMov, 0, 0));
		
		auto start = std::chrono::steady_clock::now();
		
		// rendering start
		engine.clearRender();

		engine.renderGameScene(gameScene);
		
		auto end = std::chrono::steady_clock::now();
		elapsed += std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		pc += 1;

		if (pc > 600) {
			std::cout << "Performance: " << elapsed.count() / pc << " microseconds\n";
			elapsed = std::chrono::microseconds(0);
			pc = 1;
		}

		// render end
		mainWindow.swapBuffers();
		mainWindow.pollEvents();
	}
	return 0;
}

