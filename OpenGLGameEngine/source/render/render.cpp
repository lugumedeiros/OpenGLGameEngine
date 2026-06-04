#include "../../include/render/render.h"

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

void Render::render(const Mesh& mesh, const Material& material, ShaderProgram& shaderProgram) {
	glBindVertexArray(mesh.VAO);
	glBindTexture(GL_TEXTURE_2D, material.textureID);
	glUseProgram(shaderProgram.getID());
	shaderProgram.loadUniformCache();
	glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
};
