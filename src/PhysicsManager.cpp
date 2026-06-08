#include "PhysicsManager.hpp"

PhysicsManager::PhysicsManager(EntityManager *entityManager){
    this->entityManager = entityManager;
    physicsCount = 0;
}

bool PhysicsManager::addPhysics(unsigned int entityID){
    if (physicsCount == MAX_PHYSICS)	return false;

    physics[physicsCount] = Physics(entityID, entityManager->getTransform(entityID)->position);
    physicsCount++;
    return true;
}

void PhysicsManager::update(float timeStep){
    for(int i = 0; i < physicsCount; i++){
	physics[i].update(timeStep);
	entityManager->getTransform(physics[i].ownerID)->position = physics[i].position;
    }
}
