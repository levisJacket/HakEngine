#include "Physics.hpp"

Physics::Physics(){
    inverseMass = 0.0f;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

Physics::Physics(unsigned int ownerID, glm::vec3 position, float mass){
    this->ownerID = ownerID;
    this->position = position;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
    damping = 0.95f;
    if (mass == -1.0f)	inverseMass = 0.0f;
    else 	inverseMass = 1.0f / mass;
}

void Physics::addForce(glm::vec3 force){
    forceAccum += force;
}

void Physics::addImpulse(glm::vec3 impulse){
    velocity += impulse * inverseMass;
}

void Physics::update(float duration){
    glm::vec3 acc = glm::vec3(0.0f, -9.8f, 0.0f);
 
    acc += forceAccum * inverseMass;

    acceleration = acc;
    velocity += acc * duration;

    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);

    velocity = velocity * glm::pow(damping, duration);

    position += velocity * duration;
}
