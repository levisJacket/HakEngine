#pragma once

#include "AssetLoader.hpp"
#include "EntityManager.hpp"
#include "PhysicsManager.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <string>

class Engine {
private:
    EntityManager entityManager;
    PhysicsManager physicsManager;
    Renderer renderer;

    AssetLoader assetLoader;
    Shader shader;
    
    std::vector<Light> lights;
    GLFWwindow* window;
    Camera camera;

    // Tracking entity metadata for dynamic Jolt Physics body creation
    std::unordered_map<unsigned int, float> entityMasses;

public:
    Engine() : 
	entityManager(EntityManager()),
	physicsManager(PhysicsManager(&entityManager)) {};
    ~Engine();

    bool init();
    void run();
    void terminate();

    void addLight(glm::vec3 position, glm::vec3 color);

    unsigned int createEntity(std::string name);
    Entity* getEntity(unsigned int entityID);
    void addBody(unsigned int entityID, BodyInfo info);

    void addImpulse(unsigned int entityID, glm::vec3 force);
};
