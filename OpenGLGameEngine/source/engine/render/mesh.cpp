#include "../../../include/engine/render/mesh.h"

Mesh::Mesh(GLuint meshID, GLuint indexCount, GLuint VAO, GLuint VBO, GLuint EBO):
	meshID(meshID), indexCount(indexCount), VAO(VAO), VBO(VBO), EBO(EBO) {
}

glm::mat4 Mesh::getTransform() {
	return transform;
}

void Mesh::setTransform(glm::mat4 mat4) {
	transform = mat4;
}
