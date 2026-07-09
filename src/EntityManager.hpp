#pragma once

#include "Entity.hpp"

#define MAXENTITY 8

struct physicsSet {
    unsigned int entityID;
    glm::vec3 position;
    glm::quat rotation;
};

class EntityManager{
private:
    Entity entityList[MAXENTITY];
public:
    unsigned int entityCount;
    EntityManager();
    unsigned int createEntity(Mesh *mesh);

    Entity* getEntity(unsigned int entityID);
};
