#include "Collider.hpp"

ColliderSphere::ColliderSphere(){}

ColliderSphere::ColliderSphere(unsigned int ownerID, Physics *physics){
    this->ownerID = ownerID;
    this->physics = physics;
    this->radius = 1.0f;
}
