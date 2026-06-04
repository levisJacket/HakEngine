#include "Entity.hpp"

Entity::Entity(Mesh *mesh){
    transform = Transform();
    this->mesh = mesh;
}

glm::mat4 Entity::ModelMatrix(){
    return transform.ModelMatrix();
}

unsigned int Entity::MeshVAO(){
    return mesh->GetVAO();
}

int Entity::vertexCount(){
    return mesh->GetVertexCount();
}

Transform* Entity::getTransform(){
    return &transform;
}

