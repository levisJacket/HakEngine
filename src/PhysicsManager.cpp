#include "PhysicsManager.hpp"

PhysicsManager::PhysicsManager(EntityManager *entityManager){
    this->entityManager = entityManager;
    physicsCount = 0;
}

bool PhysicsManager::addPhysics(unsigned int entityID){
    if (physicsCount == MAX_PHYSICS)	return false;

    physics[physicsCount] = Physics(entityID, entityManager->getEntity(entityID)->getPosition());
    physicsCount++;
    return true;
}

void PhysicsManager::update(float timeStep){
    for(int i = 0; i < physicsCount; i++){
	physics[i].update(timeStep);
	entityManager->getEntity(physics[i].ownerID)->setPosition(physics[i].position);
    }
}
