#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera{
    private:
	glm::mat4 projMatrix;
	glm::vec3 *location;
	glm::quat *rotation;
	float screenRatio;
	float fov;
	float near, far;
    public:
	Camera(float screenRatio);
	void SetLocation(glm::vec3 *location);
	void SetRotation(glm::quat *rotation);
	glm::mat4 ViewMatrix();
	glm::mat4 ProjectionMatrix();
};
