#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
    glm::quat rotation;
    glm::vec3 position;
    float scale;

    Transform();
    glm::mat4 ModelMatrix();
    void setRotation(float rotX, float rotY, float rotZ);
    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);
    void setScale(float scale);
};
