#pragma once

#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "Collider.hpp"
#include <memory>

#define MAX_COLLIDER 8

class CollisionManager{
private:
    std::vector<std::unique_ptr<Collider>> collider;
    EntityManager* entityManager;
    PhysicsManager* physicsManager;
    
public:
    CollisionManager();
    CollisionManager(EntityManager* entityManager, PhysicsManager* physicsManager);
    bool addCollider(unsigned int entityID, ColliderInfo data);

    void resolve(float duration);
};
