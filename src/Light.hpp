#pragma once

#include <glm/glm.hpp>

class Light{
public:
    glm::vec3 position;
    glm::vec3 color;
    Light(glm::vec3 position, glm::vec3 color);
};
