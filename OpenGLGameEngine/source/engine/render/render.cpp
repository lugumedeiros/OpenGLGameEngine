#include "../../../include/engine/render/render.h"

Render::Render(MainWindow* mainWindow) : window(mainWindow){
	setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
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

// For input controller only
void Render::setTest(float pres) {
	setTest(!isTest);
}

void Render::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::render(GameObject& gameObject) {
	// Render to current set shader program
	Mesh& mesh = gameObject.getMesh();
	glBindVertexArray(mesh.VAO);
	glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
};
