#pragma once

#include "EntityManager.hpp"
#include "Physics.hpp"
#include "Collider.hpp"

#define MAX_PHYSICS 8

class PhysicsManager{
private:
    EntityManager *entityManager;
    Physics physics[MAX_PHYSICS];
    unsigned int physicsCount;
public:
    PhysicsManager();
    PhysicsManager(EntityManager *entityManager);
    bool addPhysics(unsigned int entityID, float mass);

    Physics* getPhysics(unsigned int entityID);
     
    void update(float timeStep);

    void addImpulse(unsigned int entityID, glm::vec3 force);
};
