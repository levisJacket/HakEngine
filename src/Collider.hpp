#pragma once

#include "Physics.hpp"
#include <glm/glm.hpp>

class Collider {
public:
    unsigned int ownerID;
    Physics *physics = nullptr;
    glm::vec3 position;
};

class ColliderSphere : public Collider {
public:
    float radius;

    ColliderSphere();
    ColliderSphere(unsigned int ownerID, Physics *physics);
};
