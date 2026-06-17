#pragma once

#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "Collider.hpp"
#include "Contact.hpp"

#define MAX_COLLIDER 8

class CollisionManager{
private:
    ColliderSphere collider[MAX_COLLIDER];
    unsigned int colliderCount;
    EntityManager *entityManager;
    PhysicsManager *physicsManager;
    
public:
    CollisionManager(EntityManager *entityManager, PhysicsManager *physicsManager);
    bool addCollider(unsigned int entityID);

    void resolve(float duration);
};
