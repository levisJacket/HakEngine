#pragma once

#include "Entity.hpp"

#define MAXENTITY 8

class EntityManager{
private:
    Entity entityList[MAXENTITY];
public:
    unsigned int entityCount;
    EntityManager();
    unsigned int createEntity(Mesh *mesh);

    Entity* getEntity(unsigned int entityID);
    Transform* getTransform(unsigned int entityID);
};
