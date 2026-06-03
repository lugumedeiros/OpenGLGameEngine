#include "../../include/render/render.h"

const char* getVertexShaderSource();
const char* getFragmentShaderSource();

Render::Render(MainWindow* mainWindow) : window(mainWindow){
	setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

Render::~Render() {

}

void Render::setClearColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

void Render::setTest(bool setTest) {
	setTest ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	isTest = setTest;
}

void Render::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::render(GLuint meshID, ShaderProgram shaderProgram) {
	if (!meshs.contains(meshID)) {
		std::cout << "ERROR: RENDER OBJECT NOT FOUND" << std::endl;
		return;
	}
	Mesh& mesh = meshs.at(meshID);
	glBindVertexArray(mesh.VAO);
	glUseProgram(shaderProgram.ID);
	shaderProgram.loadUniformCache();
	glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
};

GLuint Render::newMesh(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize) {
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
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLuint meshObjID = createMeshObj(VAO, VBO, EBO, verticesToDraw);
	std::cout << "MESH '" << meshObjID << "' CREATED" << std::endl;

	return meshObjID;
}

GLuint Render::createMeshObj(GLuint VAO, GLuint VBO, GLuint EBO, GLuint verticesToDraw) {
	Mesh mesh{verticesToDraw, VAO, VBO, EBO};
	meshs.insert({ meshID, mesh });
	return meshID++;
}