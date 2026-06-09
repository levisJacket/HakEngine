#pragma once

#include "EntityManager.hpp"
#include "Physics.hpp"

#define MAX_PHYSICS 8

class PhysicsManager{
private:
    EntityManager *entityManager;
    Physics physics[MAX_PHYSICS];
    unsigned int physicsCount;
public:
    PhysicsManager(EntityManager *entityManager);
    bool addPhysics(unsigned int entityID);
    
    void update(float timeStep);
};
