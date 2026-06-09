#include "Physics.hpp"

Physics::Physics(){
    
}

Physics::Physics(unsigned int ownerID, glm::vec3 position){
    this->ownerID = ownerID;
    this->position = position;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
    damping = 0.95f;
    inverseMass = 1.0f;
}

void Physics::addForce(glm::vec3 force){
    forceAccum += force;
}

void Physics::addImpulse(glm::vec3 impulse){
    velocity = impulse * inverseMass;
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
	    velocity.y = velocity.y * -0.8;
	}
    }
}
