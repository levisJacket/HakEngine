#include "Transform.hpp"

Transform::Transform(){
    rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = 1.0f;
}

void Transform::setRotation(float rotX, float rotY, float rotZ){
    glm::quat xRotation = glm::angleAxis(rotX, glm::vec3(1, 0, 0));
    glm::quat yRotation = glm::angleAxis(rotY, glm::vec3(0, 1, 0));
    glm::quat zRotation = glm::angleAxis(rotZ, glm::vec3(0, 0, 1));
    rotation = xRotation * yRotation * zRotation;
}

void Transform::setPosition(float x, float y, float z){
    position = glm::vec3(x, y, z);
}

void Transform::setPosition(glm::vec3 position){
    this->position = position;
}

void Transform::setScale(float scale){
    this->scale = scale;
}

glm::mat4 Transform::ModelMatrix(){
    glm::mat4 matScale = {
	scale, 0.0, 0.0, 0.0,
	0.0, scale, 0.0, 0.0,
	0.0, 0.0, scale, 0.0,
	0.0, 0.0, 0.0, 1.0
    };
    glm::mat4 matRotation = glm::mat4_cast(rotation);
    glm::mat4 matPosition = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	position.x, position.y, position.z, 1.0
    };
    return matPosition * matRotation * matScale;
}
