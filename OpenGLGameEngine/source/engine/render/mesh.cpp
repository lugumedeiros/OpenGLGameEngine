#include "../../../include/engine/render/mesh.h"

Mesh::Mesh(GLuint meshID, GLuint indexCount, GLuint VAO, GLuint VBO, GLuint EBO):
	meshID(meshID), indexCount(indexCount), VAO(VAO), VBO(VBO), EBO(EBO) {
}

void Mesh::setTransform(glm::mat4 mat4) {
	transform = mat4;
}

void Mesh::scale(glm::vec3 scale3) {
	transform = glm::scale(transform, scale3);
}

void Mesh::translate(glm::vec3 pos3) {
	transform = glm::translate(transform, pos3);
}

void Mesh::resetTransform() {
	transform = glm::mat4(1.0f);
}
