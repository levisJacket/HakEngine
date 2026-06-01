#pragma once
#include "Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Entity{
    private:
	Mesh *mesh; 
	glm::vec3 location;
	glm::quat rotation;
	glm::mat4 matLocal;
    public:
	Entity(Mesh *mesh);
	glm::mat4 ModelMatrix();
	unsigned int MeshVAO();
	void SetRot(float rotX, float rotY, float rotZ);
};
