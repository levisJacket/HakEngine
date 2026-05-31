#include "Entity.hpp"

Entity::Entity(Mesh *mesh){
    location = glm::vec3(0.0f, 0.0f, 10.0f);
    rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    this->mesh = mesh;
}

unsigned int Entity::getVAO(){
    return mesh->getVAO();
}

glm::mat4 Entity::GetMat(){
    glm::mat4 matRotation = glm::mat4_cast(rotation);
    glm::mat4 matLocation = {
	1.0, 0.0, 0.0, location.x,
	0.0, 1.0, 0.0, location.y,
	0.0, 0.0, 1.0, location.z,
	0.0, 0.0, 0.0, 1.0
    };
    return matRotation * matLocation;
}

void Entity::SetRot(float rotX, float rotY, float rotZ){
    glm::quat xRotation = glm::angleAxis(rotX, glm::vec3(1, 0, 0));
    glm::quat yRotation = glm::angleAxis(rotY, glm::vec3(0, 1, 0));
    glm::quat zRotation = glm::angleAxis(rotZ, glm::vec3(0, 0, 1));
    rotation = xRotation * yRotation * zRotation;
}
