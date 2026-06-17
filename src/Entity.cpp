#include "Entity.hpp"

Entity::Entity(){
    transform = Transform();
    mesh = nullptr;
}

Entity::Entity(Mesh *mesh){
    transform = Transform();
    this->mesh = mesh;
}

glm::mat4 Entity::modelMatrix(){
    return transform.ModelMatrix();
}

unsigned int Entity::meshVAO(){
    return mesh->getVAO();
}

int Entity::vertexCount(){
    return mesh->getVertexCount();
}

void Entity::setPosition(glm::vec3 position){
    transform.position = position;
}

glm::vec3 Entity::getPosition(){
    return transform.position;
}


void Entity::setScale(float scale){
    transform.scale = scale;
}
