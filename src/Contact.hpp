#pragma once

#include "Collider.hpp"
#include <glm/glm.hpp>

class Contact {
public:
    Collider *colliderA;
    Collider *colliderB;

    glm::vec3 contactNormal;
    float penetration;
    float separatingVelocity;

    Contact();
    Contact(ColliderSphere *s1, ColliderSphere *s2);
    Contact(ColliderSphere *s, ColliderPlane *p);
    float calcSeparatingVelocity();
};


Contact buildContact(Collider *first, Collider *second);
