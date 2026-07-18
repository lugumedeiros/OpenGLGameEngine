#include "../../include/engine/engine.h"

Engine::Engine(MainWindow* window, CamBase& cam) :
	window(window),
	render(Render(window)),
	selectedCamera(cam),
	camInputControl(cam)
{
	textureService.loadAllTextures(textureDir);
	setDefaultKeyInputs();
}

// ------------ RENDER ------------ 

Mesh* Engine::createMesh(const std::vector<MeshVertex>& vertices, unsigned int* indices, unsigned int indicesSize) {
	GLuint VAO, VBO, EBO;
	GLuint verticesToDraw = indicesSize / sizeof(unsigned int);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, textureCoord));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	
	++meshID;
	Mesh mesh{ meshID, verticesToDraw, VAO, VBO, EBO };
	meshs.insert({ meshID, mesh });
	std::cout << "MESH '" << meshID << "' CREATED" << std::endl;
	return getMesh(meshID);
}

ShaderProgram* Engine::createShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath)
{
	ShaderProgram shader{ vertexSourcePath, fragmentSourcePath };
	if (shader.success) {
		GLuint id = shader.getID();
		shaderPrograms.insert({ id, shader});
		return getShaderProgram(id);
	}
	return nullptr;
}

Material* Engine::createMaterial(const ShaderProgram& shader) {
	materialID++;
	Material material{ materialID, shader.getID()};
	materials.insert({ materialID , material });
	std::cout << "MATERIAL '" << materialID << "' CREATED" << std::endl;
	return getMaterial(materialID);
}

Texture* Engine::createTexture(std::string_view texturePath) {
	return textureService.loadTexture(texturePath);
}

Texture* Engine::getTexture(std::string_view textureName) {
	return textureService.getTexture(textureName);
}

ShaderProgram* Engine::getShaderProgram(GLuint shaderProgramID) {
	try {
		return &shaderPrograms.at(shaderProgramID);
	}
	catch (const std::out_of_range& e) {
		std::cerr << "ERROR: SHADER PROGRAM '" << shaderProgramID << "'NOT FOUND\n" << e.what() << std::endl;
	}
	return nullptr;
}

Mesh* Engine::getMesh(GLuint meshID) {
	try {
		return &meshs.at(meshID);
	}
	catch (const std::out_of_range& e) {
		std::cerr << "ERROR: MESH '" << meshID << "'NOT FOUND\n" << e.what() << std::endl;
	}
	return nullptr;
}

Material* Engine::getMaterial(GLuint materialID) {
	try {
		return &materials.at(materialID);
	}
	catch (const std::out_of_range& e) {
		std::cerr << "ERROR: MATERIAL '" << materialID << "' NOT FOUND\n" << e.what() << std::endl;
	}
	return nullptr;
}

// ------------ CAMERA ------------ 

void Engine::setActiveCamera(CamBase& camera) {
	selectedCamera = camera;
	camInputControl.setCamera(selectedCamera);
}

void Engine::setUniforms(GameObject& gameObject, GameScene& gameScene, bool setGlobal) {
	Mesh& mesh = gameObject.getMesh();
	Material& material = gameObject.getMaterial();
	ShaderProgram* shader = getShaderProgram(material.shaderProgramID);

	// Global is for uniforms shared between all shaders,
	// When the same shader is called again it's not necessary to set those uniforms again
	if (setGlobal) {
		LightSourcePoint& lightSource = gameScene.getLightSource();
		LightSourcePoint& lightAmbient = gameScene.getAmbientLight();

		glm::vec3 ambientColor = lightAmbient.getColor();
		glm::vec3 sourceColor = lightSource.getColor();
		glm::vec3 sourcePos = lightSource.getPos();
		const glm::vec4& materialColor = material.getColorOverlay();
		glm::vec3 viewPos = selectedCamera.getPos();
		const glm::mat4& projection = selectedCamera.getProjection();
		const glm::mat4& view = selectedCamera.getView();
		
		// LIGHT RELATED
		glUniform3f(shader->getUniformID("ambientColor"), ambientColor.x, ambientColor.y, ambientColor.z);
		glUniform3f(shader->getUniformID("sourceLightPos"), sourcePos.x, sourcePos.y, sourcePos.z);
		glUniform3f(shader->getUniformID("sourceLightColor"), sourceColor.x, sourceColor.y, sourceColor.z);

		// MATERIAL RELATED
		glUniform1f(shader->getUniformID("specularFactor"), material.getSpecularFactor());
		glUniform1f(shader->getUniformID("shininess"), material.getShininess());

		glUniform4f(shader->getUniformID("colorOverlay"), materialColor.x, materialColor.y, materialColor.z, materialColor.w);
		glUniform1f(shader->getUniformID("colorOverlayFactor"), material.getColorOverlayFactor());
		glUniform1i(shader->getUniformID("baseTexture"), 0);
		glUniform1f(shader->getUniformID("baseTexFactor"), material.getTextureBaseFactor());
		glUniform1i(shader->getUniformID("overlayTexture"), 1);
		glUniform1f(shader->getUniformID("overlayTexFactor"), material.getTextureOverlayFactor());

		// TEXTURE BINDING
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.getTextureBaseID());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material.getTextureOverlayID());

		// VIEW RELATED
		glUniform3f(shader->getUniformID("viewPos"), viewPos.x, viewPos.y, viewPos.z);
		glUniformMatrix4fv(shader->getUniformID("uProjection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(shader->getUniformID("uView"), 1, GL_FALSE, glm::value_ptr(view));
	}

	// MESH
	glUniformMatrix4fv(shader->getUniformID("uModel"), 1, GL_FALSE, glm::value_ptr(gameObject.getTransform()));
	glUniformMatrix3fv(shader->getUniformID("uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(gameObject.getNormalMatrix()));
}

void Engine::renderGameScene(GameScene& scene) {
	ShaderProgram* lastShaderPtr = nullptr;
	for (GameObject* obj : scene.getObjects()) {
		ShaderProgram* newShaderPtr = getShaderProgram(obj->getMaterial().shaderProgramID);
		bool isDiffShader = newShaderPtr != lastShaderPtr;
		if (isDiffShader) {
			glUseProgram(newShaderPtr->getID());
			lastShaderPtr = newShaderPtr;
		}
		setUniforms(*obj, scene, isDiffShader);
		//renderMesh(*obj, scene);
		render.render(*obj);
	}
	return;
}

void Engine::clearRender() {
	lastFrameTime = glfwGetTime();
	render.clear();
}

void Engine::setTest(bool isTest) {
	render.setTest(isTest);
}

// ------------ INPUT ------------ 

void Engine::processInput() {
	double olderTime = getLastFrameTime();
	double newFrameTime = setLastFrameTime();
	inputHandler.processInput(window->getWindow(), newFrameTime);
	selectedCamera.update(static_cast<float>(newFrameTime - olderTime));
}

void Engine::configKeyInput(InputDevice device, int glfwKey, bool shouldRepeat, int firstRepeatDelay, int repeatDelay) {
	inputHandler.configKey(device, glfwKey, shouldRepeat, firstRepeatDelay, repeatDelay);
}

void Engine::setKeyInputAction(InputDevice device, int glfwKey, int glfwPressType, std::function<void(float)> action) {
	if (glfwPressType == GLFW_PRESS) {
		inputHandler.setKeyPress(device, glfwKey, action);
	}
	else if (glfwPressType == GLFW_RELEASE) {
		inputHandler.setKeyRelease(device, glfwKey, action);
	}
}

void Engine::setDefaultKeyInputs() {
	// ----- MOUSE ------- //
	
	window->enableCursor(false); //disable mouse
	inputHandler.setMouseMovX([this](float v) {camInputControl.yaw(v); });
	inputHandler.setMouseMovY([this](float v) {camInputControl.pitch(v); });

	inputHandler.setScrollAction(window->getWindow(), [this](float v) {camInputControl.zoom(v); });

	// ZOOM
	//inputHandler.setNewKey(GLFW_KEY_F, "F", true, 2, 0.1, [this](float v) { camInputControl.zoomIncrease(v); }, nullptr);
	//inputHandler.setNewKey(GLFW_KEY_F, "F", true, 2, 0.1, [this](float v) { camInputControl.zoomDecrease(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_MOUSE, GLFW_MOUSE_BUTTON_RIGHT, "MouseClickR", true, 2, 0.1,
		[this](float v) { camInputControl.zoomSet(v); },
		[this](float v) { camInputControl.zoomUnset(v);}
	);
	//inputHandler.setNewKey(DEVICE_MOUSE, GLFW_MOUSE_BUTTON_LEFT, "MouseClickL", true, 2, 0.1, [this](float v) { camInputControl.zoomUnset(v); }, nullptr);


	// ----- KEYBOARD ------- //
	// MOVEMENT
	inputHandler.setNewKey(DEVICE_KEYBOARD ,GLFW_KEY_A, "A", true, 0.01, 0, [this](float v) { camInputControl.movXNegative(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_D, "D", true, 0.01, 0, [this](float v) { camInputControl.movXPositive(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_S, "S", true, 0.01, 0, [this](float v) { camInputControl.movZNegative(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_W, "W", true, 0.01, 0, [this](float v) { camInputControl.movZPositive(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_LEFT_CONTROL, "LCTRL", true, 0.1, 0, [this](float v) { camInputControl.movYNegative(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_LEFT_SHIFT, "LSHIFT", true, 0.1, 0, [this](float v) { camInputControl.movYPositive(v); }, nullptr);
	
	// CAMERA ROTATION
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_KP_8, "n8", true, 0.01, 0, [this](float v) { camInputControl.pitchPositive(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_KP_4, "n4", true, 0.01, 0, [this](float v) { camInputControl.yawNegative(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_KP_6, "n6", true, 0.01, 0, [this](float v) { camInputControl.yawPositive(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_KP_5, "n5", true, 0.01, 0, [this](float v) { camInputControl.pitchNegative(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_E, "E", true, 0.01, 0, [this](float v) { camInputControl.rollPositive(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_Q, "Q", true, 0.01, 0, [this](float v) { camInputControl.rollNegative(v); }, nullptr);

	// CONFIG
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_T, "T", true, 2, 0.1, [this](float v) { render.setTest(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_L, "L", true, 2, 0.1, [this](float v) { camInputControl.toggleLock(v); }, nullptr);
	inputHandler.setNewKey(DEVICE_KEYBOARD, GLFW_KEY_F, "F", true, 2, 0.1, [this](float v) { camInputControl.toggleFPSMode(v); }, nullptr);
}
