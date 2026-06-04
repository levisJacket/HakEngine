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

glm::mat4 Camera::ViewMatrix(){
    glm::vec3 invLocation = - *location;
    glm::quat invRotation = glm::inverse(*rotation);

    glm::mat4 matLocation = {
	1.0, 0.0, 0.0, invLocation.x,
	0.0, 1.0, 0.0, invLocation.y,
	0.0, 0.0, 1.0, invLocation.z,
	0.0, 0.0, 0.0, 1.0
    };
    glm::mat4 matRotation = glm::mat4_cast(invRotation);
    return matLocation * matRotation;
}

glm::mat4 Camera::ProjectionMatrix(){
    return projMatrix;
}

void Camera::SetLocation(glm::vec3 *location){
    this->location = location;
}
    
void Camera::SetRotation(glm::quat *rotation){
    this->rotation = rotation;
}
