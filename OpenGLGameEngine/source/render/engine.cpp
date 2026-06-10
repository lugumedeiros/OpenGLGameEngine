#include "../../include/render/engine.h"

Engine::Engine(MainWindow* window) :
	window(window),
	render(Render(window)),
	inputHandler(InputHandler(*this)) {
	textureService.loadAllTextures(textureDir);
}

Mesh* Engine::createMesh(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize) {
	GLuint VAO, VBO, EBO;
	GLuint verticesToDraw = indicesSize / sizeof(unsigned int);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
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

void Engine::setActiveCamera(Camera* camera) {
	selectedCamera = camera;
}

void Engine::setUniforms(Mesh& mesh, Material& mat, Camera& camera) {
	ShaderProgram* shader = getShaderProgram(mat.shaderProgramID);
	//if (!mat.uniformChanged) {
	//	return;
	//}

	// View
	glUniformMatrix4fv(shader->getUniformID("uProjection"), 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
	glUniformMatrix4fv(shader->getUniformID("uView"), 1, GL_FALSE, glm::value_ptr(camera.getView()));

	// Mesh
	glUniformMatrix4fv(shader->getUniformID("uModel"), 1, GL_FALSE, glm::value_ptr(mesh.getTransform()));

	// Textures
	glUniform1f(shader->getUniformID("colorOverlayFactor"), mat.getColorOverlayFactor());
	glUniform1f(shader->getUniformID("baseTexFactor"), mat.getTextureBaseFactor());
	glUniform1f(shader->getUniformID("overlayTexFactor"), mat.getTextureOverlayFactor());

	const glm::vec4& color = mat.getColorOverlay();
	glUniform4f(shader->getUniformID("colorOverlay"), color.x, color.y, color.z, color.w);
	
	glUniform1i(shader->getUniformID("baseTexture"), 0);
	glUniform1i(shader->getUniformID("overlayTexture"), 1);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mat.getTextureBaseID());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mat.getTextureOverlayID());

	mat.uniformChanged = false;
}

void Engine::renderMesh(Mesh* mesh, Material* material) {
	if (mesh == nullptr || material == nullptr) {
		std::cerr << "ERROR: MESH OR MATERIAL PTR NULL FOR RENDERING" << std::endl;
		return;
	}
	ShaderProgram* shaderProgramPtr = getShaderProgram(material->shaderProgramID);
	if (shaderProgramPtr == nullptr) {
		std::cerr << "ERROR: SHADER PTR NULL FOR RENDERING" << std::endl;
		return;
	}
	setUniforms(*mesh, *material, *selectedCamera);
	render.render(*mesh, *material, *shaderProgramPtr);
}

void Engine::clearRender() {
	render.clear();
}

void Engine::setTest(bool isTest) {
	render.setTest(isTest);
}

void Engine::processInput() {
	inputHandler.processInput();
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

Mesh* Engine::getMesh(GLuint meshID){
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
