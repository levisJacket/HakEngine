#pragma once

#include "Entity.hpp"

#include <glm/glm.hpp>

class Physics{
    private:
	glm::vec3 position;
	glm::vec3 velocity;
	//glm::vec3 acceleration;
	glm::vec3 forceAccum;
	float damping;
	float inverseMass;

	Entity *entity;
    public:
	Physics(Entity *entity);
	void addForce(glm::vec3 force);
	void update(float duration);
};
