#pragma once

#include "EntityManager.hpp"
#include "Shader.hpp"

class Renderer{
private:
    EntityManager *entityManager;
    Shader *shader;
public:
    Renderer();
    Renderer(EntityManager *entityManager, Shader *shader);
    void render();
};
