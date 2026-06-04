#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
    private:
	glm::quat rotation;
	glm::vec3 location;
	float scale;
    
    public:
	Transform();
	glm::mat4 ModelMatrix();
	void SetRotation(float rotX, float rotY, float rotZ);
	void SetLocation(float x, float y, float z);
};
