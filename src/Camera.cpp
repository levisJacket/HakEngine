#include "Camera.hpp"

Camera::Camera(float screenRatio){
    this->screenRatio = screenRatio;
    fov = 1.0f;
    near = 0.1f;	
    far = 1000.0f;
    projMatrix = glm::mat4(
	glm::vec4(screenRatio * fov, 0.0f, 0.0f, 0.0f),
	glm::vec4(0.0f, fov, 0.0f, 0.0f),
	glm::vec4(0.0f, 0.0f, far/(far-near), -near*far/(far-near)),
	glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)
    );
}

glm::mat4 Camera::viewMatrix(){
    glm::vec3 invPosition = - *position;
    glm::quat invRotation = glm::inverse(*rotation);

    glm::mat4 matPosition = {
	1.0, 0.0, 0.0, invPosition.x,
	0.0, 1.0, 0.0, invPosition.y,
	0.0, 0.0, 1.0, invPosition.z,
	0.0, 0.0, 0.0, 1.0
    };
    glm::mat4 matRotation = glm::mat4_cast(invRotation);
    return matPosition * matRotation;
}

glm::mat4 Camera::projectionMatrix(){
    return projMatrix;
}

void Camera::setPosition(glm::vec3 *position){
    this->position = position;
}
    
void Camera::setRotation(glm::quat *rotation){
    this->rotation = rotation;
}
