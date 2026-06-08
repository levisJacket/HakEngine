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
	Entity();
	Entity(Mesh *mesh);

	glm::mat4 modelMatrix();
	unsigned int meshVAO();
	int vertexCount();

	Transform* getTransform();
};
