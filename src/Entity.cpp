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

Transform* Entity::getTransform(){
    return &transform;
}

