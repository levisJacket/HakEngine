#include "CollisionManager.hpp"
#include "Contact.hpp"
#include <vector>
#include <iostream>

CollisionManager::CollisionManager(){}

CollisionManager::CollisionManager(EntityManager* entityManager, PhysicsManager* physicsManager){
    this->entityManager = entityManager;
    this->physicsManager = physicsManager;
}

bool CollisionManager::addCollider(unsigned int entityID, ColliderInfo data){
    if (collider.size() == MAX_COLLIDER)	{
	std::cout << "failed to create; max collider reached" << std::endl;
	return false;
    }

    Physics *physics = physicsManager->getPhysics(entityID);
    if (data.type == ColliderType::Sphere){
	collider.push_back(std::make_unique<ColliderSphere>(physics, data.radius));
	return true;
    } else if (data.type == ColliderType::Plane){
	collider.push_back(std::make_unique<ColliderPlane>(physics, data.normal, data.distance));
	return true;
    }
    return false;
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
	if (c.penetration <= 0.0f) { break; }

	Physics dummy = Physics();
	Physics *physicsA = c.colliderA->physics ? c.colliderA->physics : &dummy;
	Physics *physicsB = c.colliderB->physics ? c.colliderB->physics : &dummy; 

	float massA = physicsA->inverseMass;
	float massB = physicsB->inverseMass;

	float sumMass = massA + massB;
	if (sumMass <= 0.0f) { continue; }
	
	glm::vec3 resolveUnit = c.contactNormal * c.penetration / sumMass;

	glm::vec3 moveA = resolveUnit * massA;
	glm::vec3 moveB = resolveUnit * massB * -1.0f;

	c.colliderA->position += moveA;
	c.colliderB->position += moveB;
	for (int i = 0; i < contacts.size(); i++){
	    if (i == minIndex) { continue; }

	    if (contacts[i].colliderA == c.colliderA) {
		contacts[i].penetration -= glm::dot(moveA, contacts[i].contactNormal);
	    } else if (contacts[i].colliderA == c.colliderB) {
		contacts[i].penetration -= glm::dot(moveB, contacts[i].contactNormal);
	    }

	    if (contacts[i].colliderB == c.colliderA) {
		contacts[i].penetration += glm::dot(moveA, contacts[i].contactNormal);
	    } else if (contacts[i].colliderB == c.colliderB) {
		contacts[i].penetration += glm::dot(moveB, contacts[i].contactNormal);
	    }
	}

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

