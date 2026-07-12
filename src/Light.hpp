#pragma once

#include <glm/glm.hpp>

struct Light{
public:
    glm::vec3 position;
    glm::vec3 color;
    float radius;
    float intensity;
};
