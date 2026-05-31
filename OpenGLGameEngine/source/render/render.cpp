#include "../../include/render/render.h"

const char* getVertexShaderSource();
const char* getFragmentShaderSource();

Render::Render(MainWindow* mainWindow) {
	window = mainWindow;
	compiler = ShaderCompiler();
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

void Render::render() {
	glDrawElements(GL_TRIANGLES, verticesToDraw, GL_UNSIGNED_INT, 0);
}

bool Render::setupRender(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize) {
	bool success;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	verticesToDraw = indicesSize;

	const char* vertexSource = getVertexShaderSource();
	const char* fragmentSource = getFragmentShaderSource();

	unsigned int shaderProgram;
	success = compiler.createShaderProgram(&shaderProgram, vertexSource, fragmentSource);
	if (!success) {
		return false;
	}
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	glUseProgram(shaderProgram);

	std::cout << "RENDER SETUP COMPLETE" << std::endl;
	return true;
}

const char* getVertexShaderSource() {
	const char* vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec3 pos;\n"
		"void main(){\n"
		"gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);}\n\0";
	
	return vertexShader;
}

const char* getFragmentShaderSource() {
	const char* fragmentShader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);}\n\0";
	return fragmentShader;
}