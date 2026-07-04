#include "CollisionManager.hpp"
#include "Contact.hpp"
#include <vector>
#include <iostream>

CollisionManager::CollisionManager(){}

CollisionManager::CollisionManager(EntityManager* entityManager, PhysicsManager* physicsManager){
    this->entityManager = entityManager;
    this->physicsManager = physicsManager;
}

bool CollisionManager::addCollider(unsigned int entityID){
    if (collider.size() == MAX_COLLIDER)	{
	std::cout << "failed to create; max collider reached" << std::endl;
	return false;
    }

    Physics *physics = physicsManager->getPhysics(entityID);
    collider.push_back(std::make_unique<ColliderSphere>(physics, 1.0f));

    return true;
}

void CollisionManager::resolve(float duration){
    for (int i = 0; i < collider.size(); i++){
	if (collider[i]->physics) {
	    collider[i]->position = collider[i]->physics->position;
	}
    }

    std::vector<Contact> contacts;
    for (int i = 0; i < collider.size(); i++){
	for (int j = i + 1; j < collider.size(); j++){
	    if (!collider[i]->physics && !collider[j]->physics){
		continue;
	    }

	    if (isColliding(collider[i].get(), collider[j].get())){
		Contact c = buildContact(collider[i].get(), collider[j].get());
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
	    float temp = contacts[i].calcSeparatingVelocity();
	    if (temp < minimumSep && (temp < 0.0f || contacts[i].penetration > 0.0f)){
		minimumSep = temp;
		minIndex = i;
	    }
	}

	if (minIndex == contacts.size()) { break; }

	Contact c = contacts[minIndex];
	if (c.penetration <= 0.0f) { continue; }

	Physics *physicsA = c.colliderA->physics;
	Physics *physicsB = c.colliderB->physics;

	float sumMass = physicsA->inverseMass + physicsB->inverseMass;
	if (sumMass <= 0.0f) { continue; }
	
	glm::vec3 resolveUnit = c.contactNormal * c.penetration / sumMass;

	physicsA->position += resolveUnit * physicsA->inverseMass;
	physicsB->position += resolveUnit * physicsB->inverseMass * -1.0f;

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

    for (int i = 0; i < collider.size(); i++){
	if (collider[i]->physics) {
	    collider[i]->physics->position = collider[i]->position;
	}
    }
}

