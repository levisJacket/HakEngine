#pragma once

#include "Physics.hpp"
#include <glm/glm.hpp>

enum class ColliderType{
    Sphere,
    Plane
};

struct ColliderInfo{
    ColliderType type;
    float radius;
    glm::vec3 normal;
    float distance;
};

class Collider {
public:
    Physics *physics = nullptr;
    glm::vec3 position;

protected:
    Collider(Physics *phys): physics(phys){}

public:
    virtual ~Collider() = default;

    glm::vec3 getVelocity();
};

class ColliderSphere : public Collider {
public:
    float radius;

    ColliderSphere(Physics* physics, float rad)
	: Collider{physics}, radius(rad) {}
};

class ColliderPlane : public Collider {
public:
    glm::vec3 normal;
    float distance;

    ColliderPlane();
    ColliderPlane(Physics* physics, glm::vec3 norm, float dist)
	: Collider{physics}, normal(norm), distance(dist){}
};

bool isColliding(Collider *first, Collider *second);
