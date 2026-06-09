#include "EntityManager.hpp"

EntityManager::EntityManager(){
    entityCount = 0;
}

unsigned int EntityManager::createEntity(Mesh *mesh){
    if (entityCount == MAXENTITY)	return 0;

    entityList[entityCount] = Entity(mesh);  
    entityCount += 1;
    return entityCount;
}

Entity* EntityManager::getEntity(unsigned int entityID){
    if (entityID < 1 || entityID > MAXENTITY)	return nullptr;
    return &entityList[entityID - 1];
}
