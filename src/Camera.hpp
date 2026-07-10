#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera{
    private:
	glm::mat4 projMatrix;
	glm::vec3 *position;
	glm::quat *rotation;

	float screenRatio;
	float fov;
	float near, far;
    public:
	Camera();
	Camera(float screenRatio);
	void setPosition(glm::vec3 *position);
	void setRotation(glm::quat *rotation);
	glm::mat4 viewProjectionMatrix();
};
