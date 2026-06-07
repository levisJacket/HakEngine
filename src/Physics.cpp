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
    position += velocity * duration;
    velocity += forceAccum * inverseMass;
    velocity = velocity * glm::pow(damping, duration);

    entity->transform.setPosition(position);
}
