#pragma once

#include "Collider.hpp"
#include <glm/glm.hpp>

struct Contact {
    Collider *entityA;
    Collider *entityB;

    glm::vec3 contactNormal;
    float penetration;
    float separatingVelocity;
};

