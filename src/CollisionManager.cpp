#include "CollisionManager.hpp"
#include <vector>
#include <iostream>

CollisionManager::CollisionManager(){}

CollisionManager::CollisionManager(EntityManager *entityManager, PhysicsManager *physicsManager){
    this->entityManager = entityManager;
    this->physicsManager = physicsManager;
    colliderCount = 0;
}

bool CollisionManager::addCollider(unsigned int entityID){
    if (colliderCount == MAX_COLLIDER)	return false;

    Physics *physics = physicsManager->getPhysics(entityID);
    if (physics == nullptr)	return false;

    collider[colliderCount] = ColliderSphere(entityID, physics);
    colliderCount++;
    return true;
}

void CollisionManager::resolve(float duration){
    for (int i = 0; i < colliderCount; i++){
	glm::vec3 position = entityManager->getEntity(collider[i].ownerID)->getPosition();
	collider[i].position = position;
    }

    std::vector<Contact> contacts;
    for (int i = 0; i < colliderCount; i++){
	for (int j = i + 1; j < colliderCount; j++){
	    
	    glm::vec3 diff = collider[i].position - collider[j].position;
	    float distance = glm::length(diff);
	    float radiusSum = collider[i].radius + collider[j].radius;
	    if (radiusSum > distance){
		Contact c;
		c.entityA = &collider[i];
		c.entityB = &collider[j];
		c.contactNormal = glm::normalize(diff);
		c.penetration = radiusSum - distance;
		c.separatingVelocity = glm::dot((c.entityA->physics->velocity - c.entityB->physics->velocity) , c.contactNormal);
		contacts.push_back(c);
	    }
	}
    }

    int iterationsUsed = 0;
    int iterationMax = contacts.size();

    while (iterationsUsed < iterationMax){
	float minimumSep = 1000000.0f;
	int minIndex = contacts.size();
	for (int i = 0; i < contacts.size(); i++){
	    float temp = contacts[i].separatingVelocity;
	    if (temp < minimumSep && (temp < 0.0f || contacts[i].penetration > 0.0f)){
		minimumSep = temp;
		minIndex = i;
	    }
	}

	if (minIndex == contacts.size()) { break; }

	Contact c = contacts[minIndex];
	if (c.penetration <= 0.0f) { continue; }

	Physics *physicsA = c.entityA->physics;
	Physics *physicsB = c.entityB->physics;

	float sumMass = physicsA->inverseMass + physicsB->inverseMass;
	if (sumMass <= 0.0f) { continue; }
	
	glm::vec3 resolveUnit = c.contactNormal * c.penetration / sumMass;
	c.entityA->position += resolveUnit * physicsA->inverseMass;
	c.entityB->position += resolveUnit * physicsB->inverseMass * -1.0f;

	float accCausedSepVelocity = glm::dot((physicsB->acceleration - physicsA->acceleration), c.contactNormal) * duration;

	float newSepVelocity = -c.separatingVelocity;

	if (accCausedSepVelocity < 0) {
	    newSepVelocity += accCausedSepVelocity;
	    if (newSepVelocity < 0) newSepVelocity = 0;
	}

	float restitution = 1.0f;
	newSepVelocity *= restitution;

	float deltaVelocity = newSepVelocity - c.separatingVelocity;
	
	glm::vec3 impulse = c.contactNormal * deltaVelocity / sumMass;
	physicsA->addImpulse(impulse);
	physicsB->addImpulse(-impulse);

	iterationsUsed++;
    }

    for (int i = 0; i < colliderCount; i++){
	entityManager->getEntity(collider[i].ownerID)->setPosition(collider[i].position);
    }
}

