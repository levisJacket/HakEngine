#pragma once

#include "Entity.hpp"

#include <glm/glm.hpp>

class Physics{
private:
    glm::vec3 velocity;
    glm::vec3 forceAccum;
    float damping;
    float inverseMass;

public:
    glm::vec3 position;
    unsigned int ownerID;
    Physics();
    Physics(unsigned int ownerID, glm::vec3 position);
    void addForce(glm::vec3 force);
    void addImpulse(glm::vec3 impulse);
    void update(float duration);
};
