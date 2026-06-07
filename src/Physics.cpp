#include "Physics.hpp"

Physics::Physics(Entity *entity){
    this->entity = entity;

    position = entity->transform.position;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    //acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
    damping = 0.9f;
    inverseMass = 1.0f;
}

void Physics::addForce(glm::vec3 force){
    forceAccum += force;
}

void Physics::update(float duration){
    glm::vec3 acc = glm::vec3(0.0f, -9.8f, 0.0f);
 
    acc += forceAccum * inverseMass;
    velocity += acc * duration;

    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);

    velocity = velocity * glm::pow(damping, duration);

    position += velocity * duration;
    if(position.y < 0)	{
	position.y = 0.0f;
	if (velocity.y < 0.0f) {
	    velocity.y = -velocity.y * 0.5;
	}
    }
    entity->transform.setPosition(position);
}
