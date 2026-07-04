#include "PhysicsManager.hpp"

PhysicsManager::PhysicsManager(){}

PhysicsManager::PhysicsManager(EntityManager *entityManager){
    this->entityManager = entityManager;
    physicsCount = 0;
}

bool PhysicsManager::addPhysics(unsigned int entityID, float mass){
    if (physicsCount == MAX_PHYSICS)	return false;

    physics[physicsCount] = Physics(entityID, entityManager->getEntity(entityID)->getPosition(), mass);
    physicsCount++;

    entityManager->getEntity(entityID)->hasPhysics = true;
    return true;
}

void PhysicsManager::update(float timeStep){
    for(int i = 0; i < physicsCount; i++){
	Entity *entity = entityManager->getEntity(physics[i].ownerID); 

	physics[i].position = entity->getPosition();

	physics[i].update(timeStep);

	entity->setPosition(physics[i].position);
    }
}

Physics* PhysicsManager::getPhysics(unsigned int entityID){
    for(int i = 0; i < physicsCount; i++){
	if (physics[i].ownerID == entityID){
	    return &physics[i];
	}
    }
    return nullptr;
}

void PhysicsManager::addImpulse(unsigned int entityID, glm::vec3 force){
    for(int i = 0; i < physicsCount; i++){
	if (physics[i].ownerID == entityID){
	    physics[i].addImpulse(force);
	    break;
	}
    }
}
