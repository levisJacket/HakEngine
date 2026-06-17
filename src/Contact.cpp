#include "Contact.hpp"

Contact::Contact(){}

Contact::Contact(SphereCollider *first, SphereCollider *second){
    collider[0] = first;
    collider[1] = second;
}

void Contact::resolve(float duration){
    
}

void Contact::calcContactNormal(){
    contactNormal = glm::normalize(collider[1]->physics->position - collider[0]->physics->position);
}

void Contact::calcSepVelocity(){
    calcContactNormal();
    glm::vec3 v1, v2;
    v1 = getColliderVelocity(0);
    v2 = getColliderVelocity(1);

    seperatingVelocity = glm::dot((v1 - v2), contactNormal);
}

glm::vec3 Contact::getColliderVelocity(int index){
    if (collider[index]->hasPhysics)	{
	return collider[index]->physics->velocity;
    }
    return glm::vec3(0, 0, 0);
}

