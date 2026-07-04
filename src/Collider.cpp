#include "Collider.hpp"

bool testSphereSphere(ColliderSphere *s1, ColliderSphere *s2) {
    glm::vec3 diff = s1->position - s2->position;
    float dist = glm::length(diff);
    return (s1->radius + s2->radius) >= dist;
}

bool testSpherePlane(ColliderSphere *s, ColliderPlane *p) {
    float dist = glm::dot(s->position, p->normal);
    return (dist - p->distance - s->radius <= 0);
}

bool isColliding(Collider *first, Collider *second) {
    if (auto* s1 = dynamic_cast<ColliderSphere*>(first)) {
        if (auto* s2 = dynamic_cast<ColliderSphere*>(second)) {
            return testSphereSphere(s1, s2);
        }
        if (auto* p = dynamic_cast<ColliderPlane*>(second)) {
            return testSpherePlane(s1, p);
        }
    }
    if (auto* p1 = dynamic_cast<ColliderPlane*>(first)) {
        if (auto* s = dynamic_cast<ColliderSphere*>(second)) {
            return testSpherePlane(s, p1);
        }
        if (auto* p2 = dynamic_cast<ColliderPlane*>(second)) {
            return false;
        }
    }
    return false;
}

glm::vec3 Collider::getVelocity(){
    return physics ? physics->velocity : glm::vec3(0);
}
