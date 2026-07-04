#include "Contact.hpp"

using glm::vec3;

Contact::Contact(){}

Contact::Contact(ColliderSphere *s1, ColliderSphere *s2){
    colliderA = s1;
    colliderB = s2;

    vec3 diff = s1->position - s2->position;
    float distance = glm::length(diff);
    contactNormal = glm::normalize(diff);
    penetration = s1->radius - distance;
}

Contact::Contact(ColliderSphere *s, ColliderPlane *p){
    colliderA = s;
    colliderB = p;

    contactNormal = p->normal;
    penetration =  s->radius + p->distance - glm::dot(s->position, contactNormal);
}

float Contact::calcSeparatingVelocity(){
    separatingVelocity = glm::dot(
	    colliderA->getVelocity() - colliderB->getVelocity()
	    , contactNormal);
    return separatingVelocity;
}

Contact buildContact(Collider *first, Collider *second){
    if (auto* s1 = dynamic_cast<ColliderSphere*>(first)) {
	if (auto* s2 = dynamic_cast<ColliderSphere*>(second)) {
            return Contact(s1, s2);
        }
	if (auto* p = dynamic_cast<ColliderPlane*>(second)) {
            return Contact(s1, p);
        }
    }
    if (auto* p1 = dynamic_cast<ColliderPlane*>(first)) {
        if (auto* s = dynamic_cast<ColliderSphere*>(second)) {
            return Contact(s, p1);
        }
    }
}
