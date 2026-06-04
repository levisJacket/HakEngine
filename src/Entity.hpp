#pragma once
#include "Transform.hpp"
#include "Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Entity{
    private:
	Transform transform;
	Mesh *mesh;

    public:
	Entity(Mesh *mesh);
	glm::mat4 ModelMatrix();
	unsigned int MeshVAO();
	int vertexCount();
	Transform* getTransform(); 
};
