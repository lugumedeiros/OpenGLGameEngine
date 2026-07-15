#pragma once
#include "gameObjectBase.h"

class GameObject : public GameObjectBase {
public:
	GameObject(Mesh& mesh, Material& material)
		: mesh(mesh), material(material) {
	};

	Mesh* getMeshPtr() { return &mesh; }
	Material* getMaterialPtr() { return &material; }

	Mesh& getMesh() { return mesh; }
	Material& getMaterial() { return material; }

private:

	Mesh& mesh;
	Material& material;
};