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
	bool hasPhysics = false;

	Entity();
	Entity(Mesh *mesh);

	glm::mat4 modelMatrix();
	unsigned int meshVAO();
	unsigned int meshTexture();

	int indexCount();

	Transform* getTransform();

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

	void setScale(float scale);
	float getScale();

	void setRotation(glm::quat rotation);
	glm::quat getRotation();
};
